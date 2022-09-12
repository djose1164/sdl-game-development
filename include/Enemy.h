#ifndef ENEMY_H
#define ENEMY_H

#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:
    Enemy(const LoaderParams *params);

    virtual void draw() override;
    virtual void update() override;
    virtual void clean() override;
};

#endif //ENEMY_H
