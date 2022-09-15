#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>

class GameState
{
public:
    virtual void update() = 0;
    virtual void render() = 0;

    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;

    virtual std::string stateId() const = 0;
};

#endif //GAME_STATE_H
