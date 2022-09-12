#include "Player.h"
#include "LoaderParams.h"

Player::Player(const LoaderParams *params)
    : SDLGameObject{params}
{
}

void Player::draw()
{
    SDLGameObject::draw();
}

void Player::update()
{
    --x_;
    currentFrame_ = static_cast<int>((SDL_GetTicks64() / 100) % 6);
}

void Player::clean() {}
