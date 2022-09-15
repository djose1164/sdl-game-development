#include "PlayState.h"

#include <SDL2/SDL.h>

const std::string PlayState::playId_{"PLAY"};

void PlayState::update()
{}

void PlayState::render()
{}

bool PlayState::onEnter()
{
    SDL_Log("Entering PlayState");
    return true;
}

bool PlayState::onExit()
{
    SDL_Log("Exiting PlayState");
    return true;
}

std::string PlayState::stateId() const
{
    return playId_;
}