#include "Player.h"
#include "InputHandler.h"
#include "LoaderParams.h"

Player::Player(const LoaderParams *params) : SDLGameObject{params} {}

void Player::draw() { SDLGameObject::draw(); }

void Player::update()
{
    velocity_.x(0);
    velocity_.y(0);

    handleInput();

    currentFrame_ = static_cast<int>((SDL_GetTicks64() / 100) % 6);
    SDLGameObject::update();
}

void Player::clean() {}

void Player::handleInput()
{
    if (TheInputHandler::instance()->joysticksInitialized())
    {
        auto leftXValue{TheInputHandler::instance()->xvalue(0, 1)};
        auto leftYValue{TheInputHandler::instance()->yvalue(0, 1)};

        auto rightXValue{TheInputHandler::instance()->xvalue(0, 2)};
        auto rightYValue{TheInputHandler::instance()->yvalue(0, 2)};

        if (leftXValue > 0 || leftXValue < 0)
            velocity_.x(1 * leftXValue);
        if (leftYValue > 0 || leftYValue < 0)
            velocity_.y(1 * leftYValue);

        if (rightXValue > 0 || rightXValue < 0)
            velocity_.x(1 * rightXValue);
        if (rightYValue > 0 || rightYValue < 0)
            velocity_.y(1 * rightYValue);
    }
}
