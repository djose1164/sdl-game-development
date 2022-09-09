#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game
{
public:
    Game();
    ~Game();

    void init();

    void render();
    void update();
    void handleEvents();
    void clean();

    bool running() const;

private:
    SDL_Window *window_;
    SDL_Renderer *renderer_;

    bool running_;
};

#endif //GAME_H
