#include "Level.h"

Level::Level()
{}

void Level::update()
{
    for (const auto layer: layers_)
        layer->update();
}

void Level::render()
{
    for (const auto layer: layers_)
        layer->render();
}

std::vector<Tileset> &Level::tilesets()
{
    return tilesets_;
}

std::vector<Layer *> &Level::layers()
{
    return layers_;
}
