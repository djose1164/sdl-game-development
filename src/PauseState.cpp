#include "PauseState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "LoaderParams.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "MenuState.h"

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
    auto texture{TheTextureManager::instance()};
    auto renderer{TheGame::instance()->renderer()};

    if (!texture->load("assets/resume.png", "resumeButton", renderer))
        return false;
    if (!texture->load("assets/main.png", "mainButton", renderer))
        return false;

    auto resumeButton{
        new MenuButton(
            new LoaderParams(200, 100, 200, 80, "resumeButton"),
            resumePlay
        )
    };
    auto mainButton{
        new MenuButton(
            new LoaderParams(200, 300, 200, 80, "mainButton"),
            pauseToMain
        )
    };
    gameObjects_.push_back(resumeButton);
    gameObjects_.push_back(mainButton);

    SDL_Log("Entering PauseState");
    return true;
}

bool PauseState::onExit()
{
    for (auto gameObject : gameObjects_)
        gameObject->clean();
    gameObjects_.clear();

    auto texture{TheTextureManager::instance()};
    texture->clearFromTextureMap("resumeButton");
    texture->clearFromTextureMap("mainButton");
    TheInputHandler::instance()->reset();

    SDL_Log("Exiting PauseState");
    return true;
}

std::string PauseState::stateId() const
{
    return pauseId_;
}

void PauseState::resumePlay()
{
    TheGame::instance()->gameStateMachine()->popState();
    SDL_Log("Resuming game");
}

void PauseState::pauseToMain()
{
    TheGame::instance()->gameStateMachine()->changeState(new MenuState);
}