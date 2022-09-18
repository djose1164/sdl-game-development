#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameState.h"

#include <vector>

class GameObject;
class SDLGameObject;
class PlayState : public GameState
{
public:
    void update() override;
    void render() override;

    bool onEnter() override;
    bool onExit() override;

    std::string stateId() const override;

    bool checkCollision(SDLGameObject *p1, SDLGameObject *p2);

private:
    static const std::string playId_;
    std::vector<GameObject *> gameObjects_;
};

#endif //PLAY_STATE_H

