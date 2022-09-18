#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H

#include "GameObject.h"
#include "Vector2D.h"

class LoaderParams;

class SDLGameObject : public GameObject
{
public:
    SDLGameObject(const LoaderParams *params);

    virtual void draw() override;
    virtual void update() override;
    virtual void clean() override;

    const Vector2D &position() const;

    int width() const;
    int height() const;

protected:
    int width_;
    int height_;

    int currentFrame_;
    int currentRow_;

    Vector2D position_;
    Vector2D velocity_;
    Vector2D acceleration_;

    std::string textureId_;
};

#endif // SDL_GAME_OBJECT_H
