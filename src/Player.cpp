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
        
        auto xBtnPressed{TheInputHandler::instance()->buttonState(0, 3)};
        if (xBtnPressed)
            velocity_.x(1);
        
        auto leftBtnPressed{TheInputHandler::instance()->mouseButtonState(
            static_cast<int>(TheInputHandler::MouseButtons::LEFT))
        };
        if (leftBtnPressed)
        {
            auto vec{TheInputHandler::instance()->mousePosition()};
            velocity_ = (*vec - position_) / 100;
        }

        auto theInstance{TheInputHandler::instance()};
        if (theInstance->isKeyDown(SDL_SCANCODE_LEFT))
            velocity_.x(-2);
        if (theInstance->isKeyDown(SDL_SCANCODE_RIGHT))
            velocity_.x(2);
        if (theInstance->isKeyDown(SDL_SCANCODE_UP))
            velocity_.y(-2);
        if (theInstance->isKeyDown(SDL_SCANCODE_DOWN))
            velocity_.y(2);
    }
}
