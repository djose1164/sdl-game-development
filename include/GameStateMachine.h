#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include <vector>

class GameState;

class GameStateMachine
{
public:
    void pushState(GameState *state);
    void changeState(GameState *state);
    void popState();

    void update();
    void render();

private:
    std::vector<GameState *> gameStates_;
};

#endif //GAME_STATE_MACHINE_H
