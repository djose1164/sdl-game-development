#include "AnimatedGraphic.h"
#include "LoaderParams.h"

AnimatedGraphic::AnimatedGraphic()
    : ShooterObject{}
{
}

void AnimatedGraphic::update()
{
    SDL_assert(animSpeed_);
    SDL_assert(numFrames_);
    currentFrame_ = int(((SDL_GetTicks64() / (100 / animSpeed_)) % numFrames_));
}

void AnimatedGraphic::draw()
{
    ShooterObject::draw();
}

void AnimatedGraphic::clean()
{
    ShooterObject::clean();
}

void AnimatedGraphic::load(const std::unique_ptr<LoaderParams> &params)
{
    ShooterObject::load(params);
    animSpeed_ = params->animSpeed();
    numFrames_ = params->numFrame();
}
