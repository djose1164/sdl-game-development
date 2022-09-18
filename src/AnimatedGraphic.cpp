#include "AnimatedGraphic.h"
#include <LoaderParams.h>

AnimatedGraphic::AnimatedGraphic(const LoaderParams *params, int animSpeed)
    : SDLGameObject{params}
    , animSpeed_{animSpeed}
    , numFrames_{params->numFrame()}
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