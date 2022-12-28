#include "TileLayer.h"

TileLayer::TileLayer(int tileSize, std::vector<Tileset> &tilesets)
{
}

void TileLayer::update()
{
}

void TileLayer::render()
{
}

void TileLayer::setTileIds(const std::vector<std::vector<int>> &data)
{
    tileIds_ = data;
}

void TileLayer::tileSize(int tileSize)
{
    tileSize_ = tileSize;
}

auto TileLayer::TilesetById(int tileId)
{
}
