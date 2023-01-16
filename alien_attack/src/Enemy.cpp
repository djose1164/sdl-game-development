#include "Enemy.h"
#include "LoaderParams.h"

Enemy::Enemy()
    : ShooterObject{}
{
}

Enemy::~Enemy()
{
}

std::string Enemy::type() const
{
    return "Enemy";
}
