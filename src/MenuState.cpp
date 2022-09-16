#include "MenuState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "LoaderParams.h"
#include "GameStateMachine.h"
#include "PlayState.h"

#include <SDL2/SDL.h>

const std::string MenuState::menuId_{"MENU"};

void MenuState::update()
{
    for (auto gameObject : gameObjects_)
        gameObject->update();
}

void MenuState::render()
{
    for (auto gameObject : gameObjects_)
        gameObject->draw();
}

bool MenuState::onEnter()
{
    bool result{
        !TheTextureManager::instance()->load(
            "assets/button.png", "playButton", TheGame::instance()->renderer()
        )
    };
    if (result)
        return false;

    result = !TheTextureManager::instance()->load(
        "assets/exit.png", "exitButton", TheGame::instance()->renderer()
    );
    if (result)
        return false;
    
    auto button1{
        new MenuButton(new LoaderParams(100, 100, 400, 100, "playButton"), menuToPlay)
    };
    auto button2{
        new MenuButton(new LoaderParams(100, 300, 400, 100, "exitButton"), exitFromMenu)
    };

    gameObjects_.emplace_back(button1);
    gameObjects_.emplace_back(button2);

    SDL_Log("Entering MenuState");
    return true;
}

bool MenuState::onExit()
{
    for (auto gameObject : gameObjects_)
        gameObject->clean();
    
    gameObjects_.clear();
    TheTextureManager::instance()->clearFromTextureMap("playButton");
    TheTextureManager::instance()->clearFromTextureMap("exitButton");

    SDL_Log("Exiting Menu");
    return true;
}

std::string MenuState::stateId() const
{
    return menuId_;
}

void MenuState::menuToPlay()
{
    TheGame::instance()->gameStateMachine()->changeState(new PlayState);
}

void MenuState::exitFromMenu()
{
    TheGame::instance()->quit();
}