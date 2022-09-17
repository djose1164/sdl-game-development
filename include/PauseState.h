#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "GameState.h"

#include <vector>

class GameObject;

class PauseState : public GameState
{
public:
    void update() override;
    void render() override;
    
    bool onEnter() override;
    bool onExit() override;

    std::string stateId() const override;

private:
    static void pauseToMain();
    static void resumePlay();
    
    static const std::string pauseId_;

    std::vector<GameObject *> gameObjects_;
};

#endif //PAUSE_STATE_H
