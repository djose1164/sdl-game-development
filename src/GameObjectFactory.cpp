#include "GameObjectFactory.h"

#include <algorithm>
#include <iostream>

GameObjectFactory *GameObjectFactory::instance_{nullptr};

GameObjectFactory *GameObjectFactory::instance()
{
    if (!instance_)
        instance_ =  new GameObjectFactory;

    return instance_;
}

bool GameObjectFactory::registerType(std::string typeId, BaseCreator *creator)
{
    auto itr = creators_.find(typeId);

    // If the type is already registered, do nothing.
    if (itr != creators_.end())
    {
        delete creator;
        return false;
    }

    creators_[typeId] = creator;

    for (auto key : creators_)
        std::cout << "key: " << key.first << std::endl;
    SDL_Log("creators_.size(): %ld", creators_.size());
    SDL_assert(creators_.size());
    SDL_Log("Type [%s] has been registered.", typeId.c_str());
    return true;
}

GameObject *GameObjectFactory::create(std::string typeId)
{
    auto itr = creators_.find(typeId);
    SDL_Log("creators_: size: %ld", creators_.size());
    if (itr == creators_.end())
    {
        std::cout << "Could not find type: " << typeId << std::endl;
        return nullptr;
    }

    auto creator = (*itr).second;
    SDL_assert(creator);
    SDL_Log("Type [%s] has been created.", typeId.c_str());
    return creator->createGameObject();
}
