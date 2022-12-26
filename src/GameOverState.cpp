#include "GameOverState.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "AnimatedGraphic.h"
#include "LoaderParams.h"
#include "MenuButton.h"
#include "StateParser.h"

const std::string GameOverState::gameOverId_{"GAMEOVER"};

GameOverState::~GameOverState()
{}

void GameOverState:: update()
{
    for (auto gameObject : gameObjects_)
        gameObject->update();
}

void GameOverState::render()
{
    for (auto gameObject : gameObjects_)
        gameObject->draw();
}

void GameOverState::gameOverToMain()
{
    TheGame::instance()->gameStateMachine()->changeState(new MainMenuState);
}

void GameOverState::restartPlay()
{
    TheGame::instance()->gameStateMachine()->changeState(new PlayState);
}

bool GameOverState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("assets/test.xml", gameOverId_, &gameObjects_, &textureIds_);

    callbacks_.push_back(nullptr);
    callbacks_.push_back(gameOverToMain);
    callbacks_.push_back(restartPlay);

    setCallbacks(callbacks_);

    SDL_Log("Entering GameOverState");
    return true;
}

bool GameOverState::onExit()
{
    for (auto gameObject : gameObjects_)
        gameObject->clean();
    gameObjects_.clear();
    
    for (auto id : textureIds_)
        TheTextureManager::instance()->clearFromTextureMap(id);

    SDL_Log("Exiting %s", stateId().c_str());
    return true;
}

std::string GameOverState::stateId() const
{
    return gameOverId_;
}

void GameOverState::setCallbacks(const std::vector<Callback> &callbacks)
{
    for (auto gameObject : gameObjects_)
        if (auto btn = dynamic_cast<MenuButton *>(gameObject))
            btn->callback(callbacks[btn->callbackId()]);
}
