#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "SDLGameObject.h"

class MenuButton : public SDLGameObject
{
private:
    enum class ButtonState
    {
        MOUSE_OUT,
        MOUSE_OVER,
        CLICKED
    };

public:
    MenuButton(const LoaderParams *params, void (*callback)());

    void update() override;
    void draw() override;
    void clean() override;

private:
    void (*callback_)();
    bool released_;
};

#endif // MENU_BUTTON_H