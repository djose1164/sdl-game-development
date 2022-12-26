#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H

#include "GameObject.h"
#include "Vector2D.h"

#include <string>

class LoaderParams;
class Vector2D;

class SDLGameObject : public GameObject
{
public:
    SDLGameObject();

    void draw() override;
    void update() override;
    void clean() override;

    void load(const LoaderParams *params) override;

    const Vector2D &position() const;

    int width() const;
    int height() const;

protected:
    int width_;
    int height_;

    int currentFrame_;
    int currentRow_;
    int numFrames_;

    Vector2D position_;
    Vector2D velocity_;
    Vector2D acceleration_;

    std::string textureId_;
};

#endif // SDL_GAME_OBJECT_H
