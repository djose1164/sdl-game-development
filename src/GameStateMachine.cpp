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
    if (!gameStates_.empty())
    {
        if (gameStates_.back()->stateId() == state->stateId())
            return;
        if(gameStates_.back()->onExit())
        {
            delete gameStates_.back();
            gameStates_.pop_back();
        }
    }

    gameStates_.push_back(state);
    gameStates_.back()->onEnter();
}

void GameStateMachine::popState()
{
    if (gameStates_.empty())
        return;
    if (gameStates_.back()->onExit())
    {
        delete gameStates_.back();
        gameStates_.pop_back();
    }
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