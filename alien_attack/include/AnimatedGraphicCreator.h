#ifndef ANIMATED_GRAPHIC_CREATOR_H
#define ANIMATED_GRAPHIC_CREATOR_H

#include "GameObjectFactory.h"
#include "AnimatedGraphic.h"

class AnimatedGraphicCreator : public BaseCreator
{
public:
    GameObject *createGameObject() const override { return new AnimatedGraphic; }
};

#endif // ANIMATED_GRAPHIC_CREATOR_H
