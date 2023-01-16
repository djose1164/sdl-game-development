#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include "Vector2D.h"

class LoaderParams;

class GameObject
{
public:
    virtual ~GameObject();

    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;

    virtual void load(const std::unique_ptr<LoaderParams> &params) = 0;

    virtual void collision() = 0;

    virtual std::string type() const = 0;

    Vector2D &position();
    const Vector2D &position() const;

    int width() const;
    int height() const;

    // Scroll along with the tile map.
    void scroll(float scrollSpeed);

    // Is the object currently being updated.
    bool updating() const;
    void updating(bool updating);

    bool dead() const;

    // Is the object doing a death animation
    bool dying() const;

protected:
    GameObject();

    Vector2D position_;
    Vector2D velocity_;
    Vector2D acceleration_;

    int width_;
    int height_;

    int currentRow_;
    int currentFrame_;
    int numFrame_;
    std::string textureId_;

    bool updating_;
    bool dead_;
    bool dying_;

    double angle_;

    int alpha_;
};

#endif // GAME_OBJECT_H
