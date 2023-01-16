#ifndef ENEMY_H
#define ENEMY_H

#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:
    Enemy();

    void draw() override;
    void update() override;
    void clean() override;
    
    void load(const LoaderParams *params) override;
};

#endif //ENEMY_H
