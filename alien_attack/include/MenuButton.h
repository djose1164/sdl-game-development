#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "ShooterObject.h"

class MenuButton : public ShooterObject
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

    void load(const std::unique_ptr<LoaderParams> &params) override;

    void callback(void (*callback)());
    int callbackId() const;

private:
    void (*callback_)();
    int callbackId_;
    bool released_;
};

#endif // MENU_BUTTON_H