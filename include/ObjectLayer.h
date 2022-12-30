#ifndef OBJECT_LAYER_H
#define OBJECT_LAYER_H

#include "Layer.h"

#include <vector>

class GameObject;

class ObjectLayer : public Layer
{
public:
    void update() override;

    void render() override;

    std::vector<GameObject *> &gameObjects();

private:
    std::vector<GameObject *> gameObjects_;
};

#endif //OBJECT_LAYER_H
