#include "Game.h"

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

    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    running_ = true;

    auto surface{SDL_LoadBMP("assets/animate.bmp")};
    texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
    SDL_FreeSurface(surface);

    //SDL_QueryTexture(texture_, nullptr, nullptr, &sourceRectangle_.w, &sourceRectangle_.h);

    sourceRectangle_.w = 128;
    sourceRectangle_.h = 82;

    destinationRectangle_.y = sourceRectangle_.y = 0;
    destinationRectangle_.x = sourceRectangle_.x = 0;
    destinationRectangle_.w = sourceRectangle_.w;
    destinationRectangle_.h = sourceRectangle_.h;

    return true;
}

void Game::runloop()
{
    while (running())
    {
        handleEvents();
        update();
        render();
    }
}

void Game::render()
{
    SDL_RenderClear(renderer_);

    SDL_RenderCopyEx(
        renderer_,
        texture_,
        &sourceRectangle_,
        &destinationRectangle_,
        .0,
        nullptr,
        SDL_FLIP_HORIZONTAL
    );

    SDL_RenderPresent(renderer_);
}

void Game::update()
{
    sourceRectangle_.x = 128 * static_cast<int>((SDL_GetTicks64() / 100) % 6);
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
