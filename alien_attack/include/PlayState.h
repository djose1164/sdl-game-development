#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameState.h"

#include <vector>

class GameObject;
class ShooterObject;
class Level;

class PlayState : public GameState
{
public:
    void update() override;
    void render() override;

    bool onEnter() override;
    bool onExit() override;

    std::string stateId() const override;

    bool checkCollision(ShooterObject *p1, ShooterObject *p2);

private:
    static const std::string playId_;
    std::vector<GameObject *> gameObjects_;
    Level *level_;
};

#endif //PLAY_STATE_H

