#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "GameState.h"

#include <vector>

class GameObject;

class MenuState : public GameState
{
public:
    void update() override;
    void render() override;

    bool onEnter() override;
    bool onExit() override;

    std::string stateId() const override;

private:
    static const std::string menuId_;
    std::vector<GameObject *> gameObjects_;
};

#endif // MENU_STATE_H
