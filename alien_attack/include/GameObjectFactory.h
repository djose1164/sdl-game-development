#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include "GameObject.h"

#include <map>

class BaseCreator
{
public:
    virtual GameObject *createGameObject() const = 0;
    virtual ~BaseCreator() {}
};

class GameObjectFactory
{
public:
    bool registerType(std::string typeId, BaseCreator *baseCreator);

    GameObject *create(std::string typeId);

    static GameObjectFactory *instance();

private:
    GameObjectFactory() {}
    ~GameObjectFactory() {}

    std::map<std::string, BaseCreator *> creators_;
    static GameObjectFactory *instance_;
};

using TheGameObjectFactory = GameObjectFactory;

#endif // GAME_OBJECT_FACTORY_H
