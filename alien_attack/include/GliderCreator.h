#ifndef GLIDER_CREATOR_H
#define GLIDER_CREATOR_H

#include "GameObjectFactory.h"
#include "Glider.h"

class GliderCreator : public BaseCreator
{
public:
    GameObject *createGameObject() const { return new Glider; }
};

#endif // GLIDER_CREATOR_H
