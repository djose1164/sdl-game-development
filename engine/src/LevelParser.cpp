#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "TileLayer.h"
#include "Level.h"
#include "Utils.h"
#include "ObjectLayer.h"
#include "GameObjectFactory.h"
#include "LoaderParams.h"

#include "base64.h"
#include <zlib.h>

#define for_each_ele(var, el) \
    for (auto var{(el)->FirstChildElement()}; var; var = var->NextSiblingElement()) \

Level *LevelParser::parseLevel(std::string_view levelFile)
{
    // Create a doc and load the map XML.
    tinyxml2::XMLDocument lvlDoc;
    lvlDoc.LoadFile(levelFile.data());

    auto lvl = new Level;
    auto root = lvlDoc.RootElement();

    tileSize_ = root->IntAttribute("tilewidth");
    width_ = root->IntAttribute("width");
    height_ = root->IntAttribute("height");

    const auto properties{root->FirstChildElement()};

    for (auto e{properties->FirstChildElement()}; e; e = e->NextSiblingElement())
        if (e->Value() == std::string_view{"property"})
            parseTextures(e);

    // Parse the tilesets.
    for (auto e{root->FirstChildElement()}; e; e = e->NextSiblingElement())
        if (e->Value() == std::string("tileset"))
            parseTilesets(e, &lvl->tilesets());

    // Parse any object layer.
    for (auto e{root->FirstChildElement()}; e; e = e->NextSiblingElement())
    {
        if (!(e->Value() == std::string("layer") || e->Value() == std::string_view{"objectgroup"}))
            continue;

        auto value{e->FirstChildElement()->Value()};

        if (value == std::string_view{"object"})
            parseObjectLayer(e, lvl->layers());
        else if (value == std::string_view{"data"})
            parseTileLayer(e, lvl->layers(), lvl->tilesets());
    }

    return lvl;
}

void LevelParser::parseTilesets(tinyxml2::XMLElement *tilesetRoot,
                                std::vector<Tileset> *tilesets)
{
    const auto tilesetPath{
        std::string{"assets/"} + std::string{tilesetRoot->Attribute("source")}};

    tinyxml2::XMLDocument doc{true, tinyxml2::COLLAPSE_WHITESPACE};
    if (doc.LoadFile(tilesetPath.c_str()) != tinyxml2::XML_SUCCESS)
        SDL_Log("Couldn't load [%s] file.", tilesetPath.c_str());

    const auto root{doc.RootElement()};

    const auto source{std::string{"assets/"} + root->FirstChildElement()->Attribute("source")};
    const auto id{root->Attribute("name")};

    TheTextureManager::instance()->load(
        source,
        id,
        TheGame::instance()->renderer());

    // Setup the tileset.
    Tileset tileset;
    tileset.name = id;

    tileset.width = root->FirstChildElement()->IntAttribute("width");
    tileset.height = root->FirstChildElement()->IntAttribute("height");
    tileset.tileWidth = root->IntAttribute("tilewidth");
    tileset.tileHeight = root->IntAttribute("tileheight");
    tileset.margin = root->IntAttribute("margin");
    tileset.spacing = root->IntAttribute("spacing");
    tileset.firstGridId = tilesetRoot->IntAttribute("firstgid");

    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

    tilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(tinyxml2::XMLElement *tileElement,
                                 std::vector<Layer *> &layers,
                                 const std::vector<Tileset> &tilesets)
{
    tinyxml2::XMLElement *dataNode;

    for (auto e{tileElement->FirstChildElement()}; e; e = e->NextSiblingElement())
        if (e->Value() == std::string{"data"})
            dataNode = e;

    std::string decodedIds;

    for (auto e{dataNode->FirstChild()}; e; e = e->NextSiblingElement())
    {
        auto t{std::string{e->ToText()->Value()}};
        trim(t);
        SDL_Log("[%s]: [FirstChild]: %s", __func__, t.c_str());
        decodedIds = base64_decode(std::string_view{t});
    }

    // Uncompress zlib compression.
    uLongf sizeofids{width_ * height_ * sizeof(int)};
    std::vector<int> ids(width_ * height_);

    uncompress(
        (Bytef *)&ids[0],
        &sizeofids, (const Bytef *)decodedIds.c_str(),
        decodedIds.size());

    std::vector<std::vector<int>> data;
    std::vector<int> layerRow(width_);

    for (auto i{0}; i < height_; ++i)
        data.push_back(layerRow);

    for (auto rows{0}; rows < height_; ++rows)
        for (auto cols{0}; cols < width_; ++cols)
            data[rows][cols] = ids[rows * width_ + cols];

    auto tileLayer{new TileLayer(tileSize_, tilesets)};

    tileLayer->setTileIds(data);
    layers.push_back(tileLayer);
}

void LevelParser::parseTextures(tinyxml2::XMLElement *textureRoot)
{
    TheTextureManager::instance()->load(
        textureRoot->Attribute("value"),
        textureRoot->Attribute("name"),
        TheGame::instance()->renderer()
    );
}

void LevelParser::parseObjectLayer(tinyxml2::XMLElement *objectElement, std::vector<Layer *> &layers)
{
    auto objectLayer{new ObjectLayer};
    SDL_Log("objectElement: %s", objectElement->FirstChildElement()->Value());

    for (auto e{objectElement->FirstChildElement()}; e; e = e->NextSiblingElement())
    {
        SDL_Log("e.value(): %s", e->Value());

        if (e->Value() != std::string_view{"object"})
            continue;
        
        const auto x{e->IntAttribute("x")};
        const auto y{e->IntAttribute("y")};
        const auto gameObject{TheGameObjectFactory::instance()->create(
            e->Attribute("class")
        )};

        int numFrame{};
        int textureHeight{};
        std::string textureId{};
        int textureWidth{};
        int animSpeed{};
        int callbackId{};
        // Get property values
        for_each_ele(properties, e)
        {
            if (properties->Value() != std::string_view{"properties"})
                continue;
            
            for_each_ele(property, properties)
            {
                if (property->Value() != std::string_view{"property"})
                    continue;
                
                if (property->Attribute("name") == std::string_view{"numFrame"})
                    numFrame = property->IntAttribute("value");
                else if (property->Attribute("name") == std::string_view{"textureHeight"})
                    textureHeight = property->IntAttribute("value");
                else if (property->Attribute("name") == std::string_view{"textureId"})
                    textureId = property->Attribute("value");
                else if (property->Attribute("name") == std::string_view{"textureWidth"})
                    textureWidth = property->IntAttribute("value");
                else if (property->Attribute("name") == std::string_view{"animSpeed"})
                    animSpeed = property->IntAttribute("value");
                else if (property->Attribute("name") == std::string_view{"callbackId"})
                    callbackId = property->IntAttribute("value");
            }

            gameObject->load(new LoaderParams(
                x, y, textureWidth, textureHeight, textureId
            ));
            objectLayer->gameObjects().push_back(gameObject);
        }
    }

    layers.push_back(objectLayer);
}
