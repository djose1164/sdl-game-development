#include "Player.h"
#include "InputHandler.h"
#include "LoaderParams.h"

Player::Player() : SDLGameObject{} {}

void Player::draw() { SDLGameObject::draw(); }

void Player::update()
{
    velocity_.x(0);
    velocity_.y(0);

    handleInput();

    currentFrame_ = static_cast<int>((SDL_GetTicks64() / 100) % 5);
    SDLGameObject::update();
}

void Player::clean() {}

void Player::handleInput()
{
    auto target{TheInputHandler::instance()->mousePosition()};
    velocity_ = *target - position_;
    velocity_ /= 50;
}

void Player::load(const LoaderParams *params)
{
    SDLGameObject::load(params);
}
