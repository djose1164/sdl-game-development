#include "PauseState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "LoaderParams.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "StateParser.h"

const std::string PauseState::pauseId_{"PAUSE"};

void PauseState::update()
{
    for (auto gameObject : gameObjects_)
        gameObject->update();
}

void PauseState::render()
{
    SDL_assert(gameObjects_.size());
    for (auto gameObject : gameObjects_)
        gameObject->draw();
}

bool PauseState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("assets/test.xml", pauseId_, &gameObjects_, &textureIds_);

    callbacks_.push_back(nullptr);
    callbacks_.push_back(pauseToMain);
    callbacks_.push_back(resumePlay);

    setCallbacks(callbacks_);

    SDL_Log("Entering PauseState");
    return true;
}

bool PauseState::onExit()
{
    for (auto gameObject : gameObjects_)
        gameObject->clean();
    gameObjects_.clear();

    auto texture{TheTextureManager::instance()};
    for (auto txt : textureIds_)
        texture->clearFromTextureMap(static_cast<std::string>(txt));
    TheInputHandler::instance()->reset();

    SDL_Log("Exiting PauseState");
    return true;
}

std::string PauseState::stateId() const
{
    return pauseId_;
}

void PauseState::setCallbacks(const std::vector<Callback> &callbacks)
{
    for (auto gameObject : gameObjects_)
        if(auto btn = dynamic_cast<MenuButton *>(gameObject))
            btn->callback(callbacks[btn->callbackId()]);
}

void PauseState::resumePlay()
{
    TheGame::instance()->gameStateMachine()->popState();
    SDL_Log("Resuming game");
}

void PauseState::pauseToMain()
{
    TheGame::instance()->gameStateMachine()->changeState(new MainMenuState);
}