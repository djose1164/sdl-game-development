#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"

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

    // Parse the tilesets.
    for (auto e = root->FirstChildElement(); e; e = e->NextSiblingElement())
        if (e->Value() == std::string("tileset"))
            parseTilesets(e, lvl->tilesets());

    // Parse any object layer.
    for (auto e = root->FirstChildElement(); e; e = e->NextSiblingElement())
        if (e->Value() == std::string("layer"))
            parseTileLayer(e, lvl->layers(), lvl->tilesets());

    return lvl;
}

void LevelParser::parseTilesets(tinyxml2::XMLElement *tilesetRoot,
                                std::vector<Tileset> *tilesets)
{
    const auto firstChild{tilesetRoot->FirstChildElement()};
    const auto source{firstChild->Attribute("source")};
    const auto id{firstChild->Attribute("name")};

    TheTextureManager::instance()->load(
        source,
        id,
        TheGame::instance()->renderer()
    );

    // Setup the tileset.
    Tileset tileset;
    tileset.width = firstChild->IntAttribute("width");
    tileset.height = firstChild->IntAttribute("height");
    tileset.tileWidth = firstChild->IntAttribute("tileWidth");
    tileset.tileHeight = firstChild->IntAttribute("tileHeight");
    tileset.margin = firstChild->IntAttribute("margin");
    tileset.spacing = firstChild->IntAttribute("spacing");
    tileset.firstGridId = firstChild->IntAttribute("firstGridId");

    tileset.numColumns = tileset.width / (tileset.width + tileset.spacing);

    tilesets->push_back(tileset);
}
