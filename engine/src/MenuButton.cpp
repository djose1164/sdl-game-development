#include "MenuButton.h"
#include "InputHandler.h"
#include "LoaderParams.h"
#include "Game.h"
#include "TextureManager.h"

MenuButton::MenuButton()
    : SDLGameObject{}
    , released_{true}
{
    currentFrame_ = static_cast<int>(ButtonState::MOUSE_OUT);
}

void MenuButton::draw()
{
    SDLGameObject::draw();
}

void MenuButton::update()
{
    auto mousePos{TheInputHandler::instance()->mousePosition()};

    if (mousePos->x() < position_.x() + width_ && mousePos->x() > position_.x()     // Is bound on x-axis?
        && mousePos->y() < position_.y() + height_ && mousePos->y() > position_.y() // Is bound on y-axis?
    )
    {
        if (TheInputHandler::instance()->mouseButtonState(
            static_cast<int>(TheInputHandler::MouseButtons::LEFT)
            ) 
        )
        {
            currentFrame_ = static_cast<int>(ButtonState::CLICKED);
            if (callback_ && released_)
                callback_();
            released_ = false;
        }
        else 
        {
            released_ = true;
            currentFrame_ = static_cast<int>(ButtonState::MOUSE_OVER);
        }
    }
    else
        currentFrame_ = static_cast<int>(ButtonState::MOUSE_OUT);
}

void MenuButton::clean()
{
    SDLGameObject::clean();
}

void MenuButton::load(const LoaderParams *params)
{
    SDLGameObject::load(params);
    callbackId_ = params->callbackId();
    currentFrame_ = int(ButtonState::MOUSE_OUT);
}

void MenuButton::callback(void (*callback)())
{
    callback_ = callback;
}

int MenuButton::callbackId() const
{
    return callbackId_;
}
