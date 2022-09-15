#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include <vector>

class Vector2D;

class InputHandler
{
public:
    enum class MouseButtons
    {
        LEFT,
        MIDDLE,
        RIGHT
    };

public:
    static InputHandler *instance();

    void update();
    void clean();

    void initializeJoysticks();
    bool joysticksInitialized() const;

    int xvalue(int joy, int stick) const;
    int yvalue(int joy, int stick) const;

    bool buttonState(int joy, int buttonNumber) const;

    bool mouseButtonState(int buttonNumer) const;
    Vector2D *mousePosition();
    const Vector2D *mousePosition() const;

    bool isKeyDown(SDL_Scancode key);

private:
    InputHandler();
    ~InputHandler();

    static InputHandler *instance_;

    std::vector<SDL_Joystick *> joysticks_;
    std::vector<std::pair<Vector2D *, Vector2D *>> joystickValues_;
    std::vector<std::vector<bool>> buttonStates_;
    std::vector<bool> mouseButtonStates_;

    bool joysticksInitialized_;

    const int joystickDeadZone_;

    Vector2D *mousePosition_;

    Uint8 *keyStates_;
};
typedef InputHandler TheInputHandler;

#endif // INPUT_HANDLER_H
