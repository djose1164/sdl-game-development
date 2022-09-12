#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H



#include <SDL2/SDL.h>
#include <string>

class GameObject
{
public:
    void load(int x, int y, int width, int height, std::string id);
    void draw(SDL_Renderer *renderer);
    void update();
    void clean();

protected:
    std::string textureId_;

    int currentFrame_;
    int currentRow_;

    int x_;
    int y_;

    int width_;
    int height_;
};

#endif // GAME_OBJECT_H
