#include "Game.h"
#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"
#include "LoaderParams.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"

#include <SDL2/SDL_image.h>

constexpr unsigned FPS{60};
constexpr int DELAY_TIME{static_cast<int>(1000.f/FPS)};
Uint64 frameStart, frameTime;

Game *Game::instance_{nullptr};

Game::Game()
{}

Game::~Game()
{
    if (gameStateMachine_)
        delete gameStateMachine_;
}

Game *Game::instance()
{
    if (!instance_)
        instance_ = new Game;

    return instance_;
}

bool Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    SDL_Log("Initializing game...");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    auto flags{0};
    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    window_ = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (!window_)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    if (!IMG_Init(IMG_INIT_PNG))
    {
        SDL_Log("Failed to initialize SDL_image: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    running_ = true;

    TextureManager::instance()->load("assets/animate-alpha.png", "animate", renderer_);

    gameObjects_.push_back(new Player(new LoaderParams(300, 300, 128, 82, "animate")));
    gameObjects_.push_back(new Enemy(new LoaderParams(0, 0, 128, 82, "animate")));

    TheInputHandler::instance()->initializeJoysticks();

    gameStateMachine_ = new GameStateMachine;
    gameStateMachine_->changeState(new MenuState);

    return true;
}

void Game::runloop()
{
    while (running())
    {
        frameStart = SDL_GetTicks64();

        handleEvents();
        update();
        render();

        frameTime = SDL_GetTicks64() - frameStart;
        if (frameTime < DELAY_TIME)
            SDL_Delay(static_cast<int>(DELAY_TIME - frameTime));
    }
}

void Game::render()
{
    SDL_RenderClear(renderer_);

    gameStateMachine_->render();

    SDL_RenderPresent(renderer_);
}

void Game::update()
{
    gameStateMachine_->update();
}

void Game::handleEvents()
{
    TheInputHandler::instance()->update();

    if (TheInputHandler::instance()->isKeyDown(SDL_SCANCODE_RETURN))
        gameStateMachine_->changeState(new PlayState);
}

void Game::clean()
{
    SDL_Log("Cleaning game...");
    TheInputHandler::instance()->clean();

    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);

    IMG_Quit();
    SDL_Quit();
}

void Game::quit()
{
    running_ = false;
}

bool Game::running() const
{
    return running_;
}

SDL_Renderer *Game::renderer() const
{
    return renderer_;
}
