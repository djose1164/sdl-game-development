#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameState.h"

#include <vector>

class GameObject;

class PlayState : public GameState
{
public:
    void update() override;
    void render() override;

    bool onEnter() override;
    bool onExit() override;

    std::string stateId() const override;

private:
    static const std::string playId_;
    std::vector<GameObject *> gameObjects_;
};

#endif //PLAY_STATE_H

