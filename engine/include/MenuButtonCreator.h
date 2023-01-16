#ifndef MENU_BUTTON_CREATOR_H
#define MENU_BUTTON_CREATOR_H

#include "MenuButton.h"
#include "GameObjectFactory.h"

class MenuButtonCreator : public BaseCreator
{
public:
    GameObject *createGameObject() const override { return new MenuButton; }
};

#endif //MENU_BUTTON_CREATOR_H
