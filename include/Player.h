#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject
{
public:
    void load(int x, int y, int width, int height, std::string id);
    void draw(SDL_Renderer *renderer);
    void update();
    void clean();
};

#endif // PLAYER_H
