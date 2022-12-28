#include "Level.h"

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

auto &Level::tilesets() const
{
    return tilesets_;
}

auto &Level::layers() const
{
    return layers_;
}
