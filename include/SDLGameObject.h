#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H

#include "GameObject.h"

class SDLGameObject : public GameObject
{
public:
    SDLGameObject(const LoaderParams *params);

    virtual void draw() override;
    virtual void update() override;
    virtual void clean() override;

protected:
    int x_;
    int y_;

    int width_;
    int height_;

    int currentFrame_;
    int currentRow_;

    std::string textureId_;
};

#endif // SDL_GAME_OBJECT_H
