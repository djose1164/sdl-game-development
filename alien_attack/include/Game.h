#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>

class GameObject;
class GameStateMachine;

class Game
{
public:
    ~Game();

    bool init(const char *title, int xpos, int ypos, int width, int height,
              bool fullscreen = false);

    void runloop();
    void render();
    void update();
    void handleEvents();
    void clean();
    void quit();

    bool running() const;

    static Game *instance();

    SDL_Renderer *renderer() const;

    GameStateMachine *gameStateMachine();
    const GameStateMachine *gameStateMachine() const;

    int gameWidth() const;
    int gameHeight() const;

    int scrollSpeed() const;

    void playerLives(int lives);
    int playerLives() const;

    void currentLevel(int currentLevel);
    int currentLevel() const;

    bool levelComplete() const;
    
private:
    Game();

    static Game *instance_;
    SDL_Window *window_;
    SDL_Renderer *renderer_;

    bool running_;

    std::vector<GameObject *> gameObjects_;

    GameStateMachine *gameStateMachine_;

    int width_;
    int height_;

    float scrollSpeed_;

    int playerLives_;

    int currentLevel_;
    int nextLevel_;
    bool levelComplete_;

    bool changingState_;

    std::vector<std::string> levelFiles_;
};
typedef Game TheGame;

#endif // GAME_H
