#include "GameObject.h"

GameObject::GameObject()
    : velocity_{0, 0}
    , acceleration_{0, 0}
    , width_{0}
    , height_{0}
    , currentRow_{0}
    , currentFrame_{0}
    , updating_{false}
    , dead_{false}
    , dying_{false}
    , angle_{0}
    , alpha_{255}
{
}

GameObject::~GameObject()
{
}

Vector2D &GameObject::position()
{
    return position_;
}

const Vector2D &GameObject::position() const
{
    return position_;
}

int GameObject::width() const
{
    return width_;
}

int GameObject::height() const
{
    return height_;
}

void GameObject::scroll(float scrollSpeed)
{
    position().x(position().x() - scrollSpeed);
}

bool GameObject::updating() const
{
    return updating_;
}

void GameObject::updating(bool updating)
{
    updating_ = updating;
}

bool GameObject::dead() const
{
    return dead_;
}

bool GameObject::dying() const
{
    return dying_;
}
