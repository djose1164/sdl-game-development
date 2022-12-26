#ifndef PLAYER_CREATOR_H
#define PLAYER_CREATOR_H

#include "GameObjectFactory.h"
#include "Player.h"

class PlayerCreator : public BaseCreator
{
public:
    GameObject *createGameObject() const override { return new Player; }
};

#endif // PLAYER_CREATOR_H
