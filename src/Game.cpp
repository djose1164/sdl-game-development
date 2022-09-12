#include "Game.h"
#include "TextureManager.h"

#include <SDL2/SDL_image.h>

Game::Game() {}

Game::~Game() {}

bool Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
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

    SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
    running_ = true;

    TextureManager::instance()->load("assets/animate-alpha.png", "animate", renderer_);

    go_.load(100, 100, 128, 82, "animate");
    player_.load(300, 300, 128, 82, "animate");

    return true;
}

void Game::runloop()
{
    while (running())
    {
        handleEvents();
        update();
        render();

        SDL_Delay(100);
    }
}

void Game::render()
{
    SDL_RenderClear(renderer_);

    go_.draw(renderer_);
    player_.draw(renderer_);

    SDL_RenderPresent(renderer_);
}

void Game::update()
{
    go_.update();
    player_.update();
}

void Game::handleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running_ = false;
            break;
        }
    }
}

void Game::clean()
{
    SDL_Log("Cleaning game...");
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

bool Game::running() const
{
    return running_;
}
