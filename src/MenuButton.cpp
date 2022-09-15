#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton(const LoaderParams *params)
    : SDLGameObject{params}
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
        currentFrame_ = static_cast<int>(ButtonState::MOUSE_OVER);
        if (TheInputHandler::instance()->mouseButtonState(
            static_cast<int>(TheInputHandler::MouseButtons::LEFT)
            )
        )
            currentFrame_ = static_cast<int>(ButtonState::CLICKED);
    }
    else
        currentFrame_ = static_cast<int>(ButtonState::MOUSE_OUT);
}

void MenuButton::clean()
{
    SDLGameObject::clean();
}