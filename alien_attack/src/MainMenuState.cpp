#include "MainMenuState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "LoaderParams.h"
#include "GameStateMachine.h"
#include "PlayState.h"
#include "StateParser.h"

#include <SDL2/SDL.h>

const std::string MainMenuState::menuId_{"MENU"};

void MainMenuState::update()
{
    for (auto gameObject : gameObjects_)
        gameObject->update();
}

void MainMenuState::render()
{
    for (auto gameObject : gameObjects_)  
        gameObject->draw();
    
}

bool MainMenuState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("assets/test.xml", menuId_, &gameObjects_, &textureIds_);

    callbacks_.push_back(nullptr);
    callbacks_.push_back(menuToPlay);
    callbacks_.push_back(exitFromMenu);

    // Set the callbacks for menu items.
    setCallbacks(callbacks_);

    SDL_Log("Entering MainMenuState");
    return true;
}

bool MainMenuState::onExit() /* std::vector<std::string_view> textureIds */
{
    for (auto gameObject : gameObjects_)
        gameObject->clean();
    
    gameObjects_.clear();

    for (auto id : textureIds_)
        TheTextureManager::instance()->clearFromTextureMap(id);

    SDL_Log("Exiting Menu");
    return true;
}

std::string MainMenuState::stateId() const
{
    return menuId_;
}

void MainMenuState::setCallbacks(const std::vector<Callback> &callbacks)
{
    for (auto gameObject : gameObjects_)
        if (auto btn = dynamic_cast<MenuButton *>(gameObject))
            btn->callback(callbacks[btn->callbackId()]);
}

void MainMenuState::menuToPlay()
{
    TheGame::instance()->gameStateMachine()->changeState(new PlayState);
}

void MainMenuState::exitFromMenu()
{
    TheGame::instance()->quit();
}