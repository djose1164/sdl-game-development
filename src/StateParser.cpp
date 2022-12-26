#include "StateParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "LoaderParams.h"

bool StateParser::parseState(const char *stateFile,
                             std::string_view stateId,
                             std::vector<GameObject *> *objects,
                             std::vector<std::string_view> *textureIds)
{
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(stateFile) != 0) // If failed to load.
    {
        std::cerr << doc.ErrorStr() << std::endl;
        return false;
    }

    using tinyxml2::XMLElement;

    auto root = doc.RootElement();
    XMLElement *stateRoot{nullptr};

    for (auto e = root->FirstChildElement(); e; e = e->NextSiblingElement())
    {
        if (e->Value() == stateId)
        {
            stateRoot = e;
            break;
        }
    }

    /* ---------- Parse textures ---------- */
    XMLElement *textureRoot{nullptr};

    for (auto e = stateRoot->FirstChildElement(); e; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string_view("TEXTURES"))
        {
           textureRoot = e;
           break;
        }
    }
    parseTextures(textureRoot, textureIds);

    /* ---------- Parse objects ---------- */
    XMLElement *objectRoot{nullptr};
    
    for (auto e = stateRoot->FirstChildElement(); e; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string_view("OBJECTS"))
        {
            objectRoot = e;
            break;
        }
    }
    parseObjects(objectRoot, objects);

    SDL_Log("[%s] parsed.", stateFile);
    return true;
}

void StateParser::parseTextures(tinyxml2::XMLElement *textureRoot,
                                std::vector<std::string_view> *textureIds)
{
    for (auto e = textureRoot->FirstChildElement(); e; e = e->NextSiblingElement())
    {
        std::string filenameAttr = e->Attribute("filename");
        std::string idAttr = e->Attribute("id");
        textureIds->push_back(idAttr);

        TheTextureManager::instance()->load(
            filenameAttr,
            idAttr,
            TheGame::instance()->renderer()
        );
    }
}

void StateParser::parseObjects(tinyxml2::XMLElement *objectRoot,
                               std::vector<GameObject *> *objects)
{
    for (auto e = objectRoot->FirstChildElement(); e; e = e->NextSiblingElement())
    {
        auto x = e->IntAttribute("x");
        auto y = e->IntAttribute("y");
        auto width = e->IntAttribute("width");
        auto height = e->IntAttribute("height");
        auto numFrame = e->IntAttribute("numFrame");
        auto callbackId = e->IntAttribute("callbackId");
        auto animSpeed = e->IntAttribute("animSpeed");

        std::string textureId{e->Attribute("textureId")};
        SDL_Log("textureId: %s\nx: %d\ty: %d\twidth:%d\theight: %d\ttcallbackId: %d", 
            textureId.c_str(), x, y, width, height, callbackId);

        auto gameObject{
            TheGameObjectFactory::instance()->create(e->Attribute("type"))};
        SDL_assert(gameObject);
        gameObject->load(new LoaderParams(
            x, y, width, height, textureId, numFrame, callbackId, animSpeed)
        );

        objects->push_back(gameObject);
    }
}
