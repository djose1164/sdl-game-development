#ifndef ENEMY_H
#define ENEMY_H

#include "ShooterObject.h"

class Enemy : public ShooterObject
{
public:
    virtual std::string type() const;

protected:
    Enemy();
    virtual ~Enemy();

    int health_;
};

#endif //ENEMY_H
