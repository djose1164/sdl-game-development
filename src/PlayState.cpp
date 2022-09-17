#include "PlayState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "LoaderParams.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "PauseState.h"

#include <SDL2/SDL.h>

const std::string PlayState::playId_{"PLAY"};

void PlayState::update()
{
    if (TheInputHandler::instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
        TheGame::instance()->gameStateMachine()->pushState(new PauseState);
    
    for (auto gameObject : gameObjects_)
        gameObject->update();
}

void PlayState::render()
{
    for (auto gameObject : gameObjects_)
        gameObject->draw();
}

bool PlayState::onEnter()
{
    auto result{
        TheTextureManager::instance()->load(
            "assets/helicopter.png", "helicopter", TheGame::instance()->renderer()
        )
    };
    if (!result)
        return false;
    
    auto player{new Player(new LoaderParams(100, 100, 128, 55, "helicopter"))};
    gameObjects_.push_back(player);

    SDL_Log("Entering PlayState");
    return true;
}

bool PlayState::onExit()
{
    for (auto gameObject : gameObjects_)
        gameObject->clean();
    gameObjects_.clear();
    TheTextureManager::instance()->clearFromTextureMap("helicopter");

    SDL_Log("Exiting PlayState");
    return true;
}

std::string PlayState::stateId() const
{
    return playId_;
}