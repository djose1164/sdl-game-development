#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "GameState.h"

#include <vector>

class GameObject;

class GameOverState : public GameState
{
public:
    virtual ~GameOverState();

    void update() override;
    void render() override;

    bool onEnter() override;
    bool onExit() override;

    std::string stateId() const override;

private:
    static void gameOverToMain();
    static void restartPlay();

    static const std::string gameOverId_;

    std::vector<GameObject *> gameObjects_;
};

#endif //GAME_OVER_STATE_H
