#ifndef TILE_LAYER_H
#define TILE_LAYER_H

#include "Level.h"
#include "Vector2D.h"

class TileLayer : public Layer
{
public:
    TileLayer(int tileSize, const std::vector<Tileset> &tilesets);

    void update() override;
    void render() override;

    void setTileIds(const std::vector<std::vector<int>> &data);

    void tileSize(int tileSize);

    Tileset tilesetById(int tileId);

private:
    int numColumns_;
    int numRows_;
    int tileSize_;

    Vector2D position_;
    Vector2D velocity_;

    const std::vector<Tileset> &tilesets_;

    std::vector<std::vector<int>> tileIds_;
};

#endif // TILE_LAYER_H
