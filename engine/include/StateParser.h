#include <iostream>
#include <vector>
#include <tinyxml2.h>

class GameObject;

class StateParser
{
public:
    bool parseState(const char *stateFile, std::string_view stateId,
                    std::vector<GameObject *> *objects,
                    std::vector<std::string_view> *textureIds);

private:
    void parseObjects(tinyxml2::XMLElement *objectRoot,
                      std::vector<GameObject *> *objects);

    void parseTextures(tinyxml2::XMLElement *textureRoot,
                       std::vector<std::string_view> *textureIds);
};