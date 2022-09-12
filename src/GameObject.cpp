#include "GameObject.h"
#include "TextureManager.h"

void GameObject::load(int x, int y, int width, int height, std::string id)
{
    x_ = x;
    y_ = y;
    width_ = width;
    height_ = height;

    textureId_ = id;
    currentFrame_ = currentRow_ = 1;
}

void GameObject::draw(SDL_Renderer *renderer)
{
    TextureManager::instance()->drawFrame(
        textureId_,
        x_,
        y_,
        width_,
        height_,
        currentRow_,
        currentFrame_,
        renderer
    );
}

void GameObject::update()
{
    currentFrame_ = static_cast<int>((SDL_GetTicks64() / 100) % 6);

    ++x_;
}
