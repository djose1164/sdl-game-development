#include "GameOverState.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "AnimatedGraphic.h"
#include "LoaderParams.h"
#include "MenuButton.h"

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
    TheGame::instance()->gameStateMachine()->changeState(new MenuState);
}

void GameOverState::restartPlay()
{
    TheGame::instance()->gameStateMachine()->changeState(new PlayState);
}

bool GameOverState::onEnter()
{
    auto texture{TheTextureManager::instance()};
    const auto renderer{TheGame::instance()->renderer()};

    if (!texture->load("assets/gameover.png", "gameOverText", renderer))
        return false;
    if (!texture->load("assets/main.png", "mainButton", renderer))
        return false;
    if (!texture->load("assets/restart.png", "restartButton", renderer))
        return false;
    
    auto gameOverText{
        new AnimatedGraphic(
            new LoaderParams(200, 100, 190, 30, "gameOverText", 2), 1
        )
    };
    auto mainButton{
        new MenuButton(
            new LoaderParams(200, 200, 200, 80, "mainButton"), gameOverToMain
        )
    };
    auto restartButton{
        new MenuButton(
            new LoaderParams(200, 300, 200, 80, "restartButton"), restartPlay
        )
    };

    gameObjects_.push_back(gameOverText);
    gameObjects_.push_back(mainButton);
    gameObjects_.push_back(restartButton);

    SDL_Log("Entering GameOverState");
    return true;
}

bool GameOverState::onExit()
{
    for (auto gameObject : gameObjects_)
        gameObject->clean();
    gameObjects_.clear();
    
    TheTextureManager::instance()->clearFromTextureMap("gameOverText");
    TheTextureManager::instance()->clearFromTextureMap("mainButton");
    TheTextureManager::instance()->clearFromTextureMap("restartButton");

    SDL_Log("Exiting %s", stateId().c_str());
    return true;
}

std::string GameOverState::stateId() const
{
    return gameOverId_;
}