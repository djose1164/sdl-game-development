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
    MenuButton();

    void update() override;
    void draw() override;
    void clean() override;

    void load(const LoaderParams *params) override;

    void callback(void (*callback)());
    int callbackId() const;

private:
    void (*callback_)();
    int callbackId_;
    bool released_;
};

#endif // MENU_BUTTON_H