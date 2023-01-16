#include "GameStateMachine.h"
#include "GameState.h"

#include <SDL2/SDL.h>

void GameStateMachine::pushState(GameState *state)
{
    gameStates_.push_back(state);
    gameStates_.back()->onEnter();
}

void GameStateMachine::changeState(GameState *state)
{
    SDL_assert(state);
    SDL_Log("Changing state");
    if (!gameStates_.empty())
    {
        if (gameStates_.back()->stateId() == state->stateId())
            return;
        if(gameStates_.back()->onExit())
            gameStates_.pop_back();
        else // Error on exit, keep in the same state.
            return;
    }

    gameStates_.push_back(state);
    gameStates_.back()->onEnter();
    SDL_Log("State changed");
}

void GameStateMachine::popState()
{
    SDL_assert(gameStates_.size());
    if (gameStates_.empty())
        return;
    gameStates_.back()->onExit();
    gameStates_.pop_back();

    SDL_Log("Popping state");
}

void GameStateMachine::update()
{
    if (!gameStates_.empty())
        gameStates_.back()->update();
}

void GameStateMachine::render()
{
    if (!gameStates_.empty())
        gameStates_.back()->render();
}

void GameStateMachine::clean()
{
    
}