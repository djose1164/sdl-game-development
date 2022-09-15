#include "InputHandler.h"
#include "Game.h"
#include "Vector2D.h"

InputHandler *InputHandler::instance_{nullptr};
constexpr unsigned NUM_OF_BUTTON_MOUSE{3};

InputHandler::InputHandler()
    : joysticksInitialized_{false}
    , joystickDeadZone_{10'000}
    , mousePosition_{new Vector2D(0, 0)}
{
    for (auto i{0}; i < NUM_OF_BUTTON_MOUSE; ++i)
        mouseButtonStates_.push_back(false);
}

InputHandler::~InputHandler()
{
    if (mousePosition_)
        delete mousePosition_;
}

InputHandler *InputHandler::instance()
{
    if (!instance_)
        instance_ = new InputHandler;
    return instance_;
}

void InputHandler::initializeJoysticks()
{
    if (!SDL_WasInit(SDL_INIT_JOYSTICK))
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);

    if (SDL_NumJoysticks() > 0)
    {
        for (decltype(SDL_NumJoysticks()) i{0}; i < SDL_NumJoysticks(); ++i)
        {
            auto joy{SDL_JoystickOpen(i)};
            if (!joy)
            {
                SDL_Log("Couldn't open joystick: %s", SDL_GetError());
                continue;
            }

            joysticks_.emplace_back(joy);
            joystickValues_.emplace_back(std::make_pair(new Vector2D(0.f, 0.f), new Vector2D(0.f, 0.f)));

            std::vector<bool> tempButtons;
            for (auto i{0}; i < SDL_JoystickNumButtons(joy); ++i)
                tempButtons.push_back(false);
            buttonStates_.emplace_back(tempButtons);
        }

        SDL_JoystickEventState(SDL_ENABLE);
        joysticksInitialized_ = true;
        SDL_Log("Initialized %ld joystick(s)", joysticks_.size());
    }
    else
        joysticksInitialized_ = false;
}

bool InputHandler::joysticksInitialized() const
{
    return joysticksInitialized_;
}

void InputHandler::clean()
{
    if (!joysticksInitialized_)
        return;
    for (decltype(SDL_NumJoysticks()) i = 0; i < SDL_NumJoysticks(); ++i)
        SDL_JoystickClose(joysticks_[i]);
}

void InputHandler::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        keyStates_ = const_cast<Uint8 *>(SDL_GetKeyboardState(nullptr));

        auto whichOne{event.jaxis.which};
        auto axis{event.jaxis.axis};
        auto value{event.jaxis.value};
        auto button{event.jbutton.button};
        auto mouseButton{event.button.button};

        switch (event.type)
        {
        case SDL_QUIT:
            TheGame::instance()->quit();
            break;

        case SDL_JOYAXISMOTION:
            // Left stick move left or right.
            if (axis == 0)
            {
                if (value > joystickDeadZone_)
                    joystickValues_[whichOne].first->x(1);
                else if (value < -joystickDeadZone_)
                    joystickValues_[whichOne].first->x(-1);
                else
                    joystickValues_[whichOne].first->x(0);
            }
            // Left stick move up or down. y-axis
            if (axis == 1)
            {
                if (value > joystickDeadZone_)
                    joystickValues_[whichOne].first->y(1);
                else if (value < -joystickDeadZone_)
                    joystickValues_[whichOne].first->y(-1);
                else
                    joystickValues_[whichOne].first->y(0);
            }
            // Right stick move left or right
            if (axis == 2)
            {
                if (value > joystickDeadZone_)
                    joystickValues_[whichOne].second->x(1);
                else if (value < -joystickDeadZone_)
                    joystickValues_[whichOne].second->x(-1);
                else
                    joystickValues_[whichOne].second->x(0);
            }
            // Right stick move up or down
            if (axis == 3)
            {
                if (value > joystickDeadZone_)
                    joystickValues_[whichOne].second->y(1);
                else if (value < -joystickDeadZone_)
                    joystickValues_[whichOne].second->y(-1);
                else
                    joystickValues_[whichOne].second->y(0);
            }
            break;

        case SDL_JOYBUTTONUP:
            buttonStates_[whichOne][button] = false;
            break;

        case SDL_JOYBUTTONDOWN:
            buttonStates_[whichOne][button] = true;
            break;

        case SDL_MOUSEBUTTONDOWN:
            switch (mouseButton)
            {
            case SDL_BUTTON_LEFT:
                mouseButtonStates_[static_cast<int>(MouseButtons::LEFT)] = true;
                break;
            case SDL_BUTTON_MIDDLE:
                mouseButtonStates_[static_cast<int>(MouseButtons::MIDDLE)] = true;
                break;
            case SDL_BUTTON_RIGHT:
                mouseButtonStates_[static_cast<int>(MouseButtons::RIGHT)] = true;
            }
            break;
        
        case SDL_MOUSEBUTTONUP:
            switch (mouseButton)
            {
            case SDL_BUTTON_LEFT:
                mouseButtonStates_[static_cast<int>(MouseButtons::LEFT)] = false;
                break;
            case SDL_BUTTON_MIDDLE:
                mouseButtonStates_[static_cast<int>(MouseButtons::MIDDLE)] = false;
                break;
            case SDL_BUTTON_RIGHT:
                mouseButtonStates_[static_cast<int>(MouseButtons::RIGHT)] = false;
            }
            break;

        case SDL_MOUSEMOTION:
            mousePosition_->x(event.motion.x);
            mousePosition_->y(event.motion.y); 
        } // switch (event.type)
    }
}

int InputHandler::xvalue(int joy, int stick) const
{
    if (joystickValues_.size())
    {
        if (stick == 1)
            return joystickValues_[joy].first->x();
        else if (stick == 2)
            return joystickValues_[joy].second->x();
    }
    return 0;
}

int InputHandler::yvalue(int joy, int stick) const
{
    if (joystickValues_.size())
    {
        if (stick == 1)
            return joystickValues_[joy].first->y();
        else if (stick == 2)
            return joystickValues_[joy].second->y();
    }
    return 0;
}

bool InputHandler::buttonState(int joy, int buttonNumber) const
{
    return buttonStates_[joy][buttonNumber];
}

bool InputHandler::mouseButtonState(int buttonNumer) const
{
    return mouseButtonStates_[buttonNumer];
}

Vector2D *InputHandler::mousePosition()
{
    return mousePosition_;
}

const Vector2D *InputHandler::mousePosition() const
{
    return mousePosition_;
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if (!keyStates_)
        return false;
    if (keyStates_[key])
        return true;
        
    return false;
}