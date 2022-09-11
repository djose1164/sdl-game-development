#ifndef GAME_H
#define GAME_H

#include "TextureManager.h"

#include <SDL2/SDL.h>

class Game
{
public:
    Game();
    ~Game();

    bool init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen = false);

    void runloop();
    void render();
    void update();
    void handleEvents();
    void clean();

    bool running() const;

private:
    SDL_Window *window_;
    SDL_Renderer *renderer_;

    TextureManager textureManager_;

    int currentFrame_;

    bool running_;
};

#endif //GAME_H
