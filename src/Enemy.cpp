#include "Enemy.h"
#include "LoaderParams.h"

Enemy::Enemy(const LoaderParams *params)
    : SDLGameObject(params)
{}

void Enemy::draw()
{
    SDLGameObject::draw();
}

void Enemy::update()
{
    ++x_;
    ++y_;
    currentFrame_ = static_cast<int>((SDL_GetTicks64() / 100) % 6);
}

void Enemy::clean() {}
