#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H

#include "Level.h"

#include <string_view>
#include <tinyxml2.h>

class LevelParser
{
public:
    Level *parseLevel(std::string_view levelFile);

private:
    void parseTilesets(tinyxml2::XMLElement *tilesetRoot, std::vector<Tileset> *tilesets);

    void parseTileLayer(tinyxml2::XMLElement *tileElement, std::vector<Layer *> &layers,
                        const std::vector<Tileset> &tilesets);

    int tileSize_;
    int width_;
    int height_;
};

#endif // LEVEL_PARSER_H
