#include "PlayState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "LoaderParams.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "PauseState.h"
#include "Enemy.h"
#include "GameOverState.h"
#include "SDLGameObject.h"

#include <SDL2/SDL.h>

const std::string PlayState::playId_{"PLAY"};

void PlayState::update()
{
    if (TheInputHandler::instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
        TheGame::instance()->gameStateMachine()->pushState(new PauseState);
    
    for (auto gameObject : gameObjects_)
        gameObject->update();
    
    if (checkCollision(
            dynamic_cast<SDLGameObject *>(gameObjects_[0]), 
            dynamic_cast<SDLGameObject *>(gameObjects_[1])
        )
    )
        TheGame::instance()->gameStateMachine()->pushState(new GameOverState);
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
    
    auto player{new Player(new LoaderParams(500, 100, 128, 55, "helicopter"))};
    auto enemy{new Enemy(new LoaderParams(100, 100, 128, 55, "helicopter"))};
    gameObjects_.push_back(player);
    gameObjects_.push_back(enemy);

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

bool PlayState::checkCollision(SDLGameObject *p1, SDLGameObject *p2)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = p1->position().x();
    rightA = leftA + p1->width();
    topA = p1->position().y();
    bottomA = topA + p1->height();

    leftB = p2->position().x();
    rightB = leftB + p2->width();
    topB = p2->position().y();
    bottomB = topB + p2->height();

    if (bottomA <= topB)
        return false;
    if (topA >= bottomB)
        return false;
    if (rightA <= leftB)
        return false;
    if (leftA >= rightB)
        return false;

    return true;
}