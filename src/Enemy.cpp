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
    position_.x(position_.x() + 1);
    position_.y(position_.y() + 1);
    currentFrame_ = static_cast<int>((SDL_GetTicks64() / 100) % 6);
}

void Enemy::clean() {}
