#include "Player.h"

void Player::load(int x, int y, int width, int height, std::string id)
{
    GameObject::load(x, y, width, height, id);
}

void Player::draw(SDL_Renderer *renderer)
{
    GameObject::draw(renderer);
}

void Player::update()
{
    currentFrame_ = static_cast<int>((SDL_GetTicks64() / 100) % 6);
    --x_;
}
