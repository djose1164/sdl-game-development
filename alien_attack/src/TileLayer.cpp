#include "TileLayer.h"
#include "Game.h"
#include "TextureManager.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset> &tilesets)
    : tileSize_{tileSize}
    , position_{0, 0}
    , velocity_{0, 0}
    , tilesets_{tilesets}
{
    numColumns_ = TheGame::instance()->gameWidth() / tileSize_;
    numRows_ = TheGame::instance()->gameHeight() / tileSize_;
}

void TileLayer::update()
{
    position_ += velocity_;
}

void TileLayer::render()
{
    auto x{int(position_.x() / tileSize_)};
    auto y{int(position_.y() / tileSize_)};

    auto x2{int(position_.x()) % tileSize_};
    auto y2{int(position_.y()) % tileSize_};

    for (auto i{0}; i < 15; ++i)
    {
        for (auto j{0}; j < numColumns_; ++j)
        {
            auto id{tileIds_[i][j + x]};
            if (id == 0)
                continue;
            auto tileset{tilesetById(id)};

            --id;

            TheTextureManager::instance()->drawTile(
                tileset.name,
                tileset.margin,
                tileset.spacing,
                (j*tileSize_) - x2,
                (i*tileSize_) - y2,
                tileSize_,
                tileSize_,
                (id - (tileset.firstGridId - 1)) / tileset.numColumns,
                (id - (tileset.firstGridId - 1)) % tileset.numColumns,
                TheGame::instance()->renderer()
            );
        }
    }
}

void TileLayer::setTileIds(const std::vector<std::vector<int>> &data)
{
    tileIds_ = data;
}

void TileLayer::tileSize(int tileSize)
{
    tileSize_ = tileSize;
}

Tileset TileLayer::tilesetById(int tileId)
{
    for (auto i{0}; i < tilesets_.size(); ++i)
    {
        if (!(i + 1  <= tilesets_.size() - 1))
            return tilesets_[i];

        if (tileId >= tilesets_[i].firstGridId && tileId < tilesets_[i + 1].firstGridId)
            return tilesets_[i];
    }

    SDL_Log("Didn't find tileset, returning empty tileset");

    return {};
}
