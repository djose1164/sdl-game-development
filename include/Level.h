#ifndef LEVEL_H
#define LEVEL_H

#include "Layer.h"

#include <string>
#include <vector>

/**
 * @brief This struct holds any information we need to know about our tilesets.
 *
 */
struct Tileset
{
    int firstGridId;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;

    std::string name;
};

class Level
{
public:
    ~Level() = default;

    void update();
    void render();

    /**
     * @brief Return the the tilesets.
     *
     * @return auto& Reference to the tilesets.
     */
    auto &tilesets() const;

    /**
     * @brief Return the the layers.
     *
     * @return auto& Reference to the layers.
     */
    auto &layers() const;

private:
    friend class LevelParser;
    Level();

    std::vector<Tileset> tilesets_;
    std::vector<Layer *> layers_;
};

#endif // LEVEL_H
