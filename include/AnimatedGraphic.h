#ifndef ANIMATED_GRAPHIC_H
#define ANIMATED_GRAPHIC_H

#include "SDLGameObject.h"

class LoaderParams;

class AnimatedGraphic : public SDLGameObject
{
public:
    AnimatedGraphic();

    void update() override;
    void draw() override;
    void clean() override;

    void load(const LoaderParams *params) override;

private:
    int animSpeed_;
    int numFrames_;
};

#endif // ANIMATED_GRAPHIC_H
