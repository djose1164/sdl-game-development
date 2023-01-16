#include "AnimatedGraphic.h"
#include "LoaderParams.h"

AnimatedGraphic::AnimatedGraphic()
    : SDLGameObject{}
{}

void AnimatedGraphic::update()
{
    SDL_assert(animSpeed_);
    SDL_assert(numFrames_);
    currentFrame_ = int(((SDL_GetTicks64() / (100 / animSpeed_)) % numFrames_));
}

void AnimatedGraphic::draw()
{
    SDLGameObject::draw();
}

void AnimatedGraphic::clean()
{
    SDLGameObject::clean();
}

void AnimatedGraphic::load(const LoaderParams *params)
{
    SDLGameObject::load(params);
    animSpeed_ = params->animSpeed();
    numFrames_ = params->numFrame();
}
