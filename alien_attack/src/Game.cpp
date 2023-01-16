#include "Game.h"
#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"
#include "LoaderParams.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "GameObjectFactory.h"
#include "MenuButtonCreator.h"
#include "PlayerCreator.h"
#include "GliderCreator.h"
#include "AnimatedGraphicCreator.h"
#include "SoundManager.h"
#include "GameOverState.h"
#include "ScrollingBackground.h"

#include <SDL2/SDL_image.h>

constexpr unsigned FPS{60};
constexpr int DELAY_TIME{static_cast<int>(1000.f/FPS)};
Uint64 frameStart, frameTime;

Game *Game::instance_{nullptr};

Game::Game()
    : window_{nullptr}
    , renderer_{nullptr}
    , running_{false}
    , gameStateMachine_{nullptr}
    , scrollSpeed_{.8f}
    , playerLives_{3}
    , levelComplete_{false}
    , changingState_{false}
{
    levelFiles_.push_back("assets/map1.tmx");

    currentLevel_ = 1;
}

Game::~Game()
{
    renderer_ = nullptr;
    window_ = nullptr;   
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
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    auto flags{0};
    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    window_ = SDL_CreateWindow(title, xpos, ypos, width_ = width, height_ = height, flags);
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

    TheSoundManager::instance()->load("assets/DST_ElectroRock.ogg", "DST_ElectroRock", SoundType::SOUND_MUSIC);
    TheSoundManager::instance()->playMusic("DST_ElectroRock", -1);

    TheInputHandler::instance()->initializeJoysticks();

    SDL_Log("Registering types...");
    TheGameObjectFactory::instance()->registerType("MenuButton", new MenuButtonCreator);
    TheGameObjectFactory::instance()->registerType("Player", new PlayerCreator);
    TheGameObjectFactory::instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator);
    TheGameObjectFactory::instance()->registerType("Glider", new GliderCreator);
    TheGameObjectFactory::instance()->registerType("ScrollingBackground", new ScrollingBackgroundCreator);

    gameStateMachine_ = new GameStateMachine;
    SDL_assert(gameStateMachine_);
    gameStateMachine_->changeState(new MainMenuState);

    running_ = true;
    SDL_Log("Game started!");
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

    gameStateMachine_->clean();
    gameStateMachine_ = nullptr;
    delete gameStateMachine_;

    TheTextureManager::instance()->clearTextureMap();

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

GameStateMachine *Game::gameStateMachine()
{
    return gameStateMachine_;
}

const GameStateMachine *Game::gameStateMachine() const
{
    return gameStateMachine_;
}

int Game::gameWidth() const
{
    return width_;
}

int Game::gameHeight() const
{
    return height_;
}

int Game::scrollSpeed() const
{
    return scrollSpeed_;
}

void Game::playerLives(int lives)
{
    if (lives > 0)
        playerLives_ = lives;
}

int Game::playerLives() const
{
    return playerLives_;
}

void Game::currentLevel(int currentLevel)
{
    currentLevel_ = currentLevel_;
    gameStateMachine_->changeState(new GameOverState);
    levelComplete_ = false;
}

int Game::currentLevel() const
{
    return currentLevel_;
}

bool Game::levelComplete() const
{
    return levelComplete_;
}
