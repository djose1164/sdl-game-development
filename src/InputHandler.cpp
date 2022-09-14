#include "InputHandler.h"
#include "Game.h"
#include "Vector2D.h"

InputHandler *InputHandler::instance_{nullptr};

InputHandler::InputHandler()
	: joysticksInitialized_{false}
    , joystickDeadZone_{10'000}
{}

InputHandler::~InputHandler() {}

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
		if (event.type == SDL_QUIT)
			TheGame::instance()->quit();

        if (event.type == SDL_JOYAXISMOTION)
        {
            auto whichOne{event.jaxis.which};
            auto axis{event.jaxis.axis};
            auto value{event.jaxis.value};

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
        }
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

