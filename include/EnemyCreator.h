#ifndef ENEMY_CREATOR_H
#define ENEMY_CREATOR_H

#include "GameObjectFactory.h"
#include "Enemy.h"

class EnemyCreator : public BaseCreator
{
public:
    GameObject *createGameObject() const override { return new Enemy; }
};

#endif // ENEMY_CREATOR_H
