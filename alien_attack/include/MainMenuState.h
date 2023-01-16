#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "MenuState.h"

#include <vector>

class GameObject;

class MainMenuState : public MenuState
{
public:
    void update() override;
    void render() override;

    bool onEnter() override;
    bool onExit() override;

    std::string stateId() const override;

private:
    void setCallbacks(const std::vector<Callback> &callbacks) override;

    std::vector<GameObject *> gameObjects_;

    static const std::string menuId_;
    static void menuToPlay();
    static void exitFromMenu();
};

#endif // MAIN_MENU_STATE_H
