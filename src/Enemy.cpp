#include "Enemy.h"
#include "LoaderParams.h"

Enemy::Enemy()
    : SDLGameObject()
{
    velocity_.x(.001f);
    velocity_.y(2.f);
}

void Enemy::draw()
{
    SDLGameObject::draw();
}

void Enemy::update()
{
    currentFrame_ = static_cast<int>((SDL_GetTicks64() / 100) % 5);

    if (position_.y() < 0)
        position_.y(2);
    else if (position_.y() > 400)
        position_.y(-2);

    SDLGameObject::update();
}

void Enemy::clean() {}

void Enemy::load(const LoaderParams *params)
{
    SDLGameObject::load(params);
    velocity_.x(.001f);
    velocity_.y(2.f);
}
