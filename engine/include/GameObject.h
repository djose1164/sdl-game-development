#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL2/SDL.h>
#include <string>

class LoaderParams;

class GameObject
{
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;

    virtual void load(const LoaderParams* params) = 0;

protected:
    GameObject();
    virtual ~GameObject();
};

#endif // GAME_OBJECT_H
