#include "ObjectLayer.h"
#include "GameObject.h"

void ObjectLayer::update()
{
    for (const auto gameObject: gameObjects_)
        gameObject->update();
}

void ObjectLayer::render()
{
    for (const auto gameObject: gameObjects_)
        gameObject->draw();
}

std::vector<GameObject *> &ObjectLayer::gameObjects()
{
    return gameObjects_;
}
