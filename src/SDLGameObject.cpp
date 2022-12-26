#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject()
    : GameObject{}
{
}

void SDLGameObject::draw()
{
    if (velocity_.x() > 0)
        TextureManager::instance()->drawFrame(
            textureId_,
            static_cast<Uint32>(position_.x()),
            static_cast<Uint32>(position_.y()),
            width_,
            height_,
            currentRow_,
            currentFrame_,
            TheGame::instance()->renderer(),
            SDL_FLIP_HORIZONTAL);
    else
        TextureManager::instance()->drawFrame(
            textureId_,
            static_cast<Uint32>(position_.x()),
            static_cast<Uint32>(position_.y()),
            width_,
            height_,
            currentRow_,
            currentFrame_,
            TheGame::instance()->renderer());
}

void SDLGameObject::update()
{
    velocity_ += acceleration_;
    position_ += velocity_;
}

void SDLGameObject::clean()
{
}

const Vector2D &SDLGameObject::position() const
{
    return position_;
}

int SDLGameObject::width() const
{
    return width_;
}

int SDLGameObject::height() const
{
    return height_;
}

void SDLGameObject::load(const LoaderParams *params)
{
    position_ = Vector2D{float(params->x()), float(params->y())};
    velocity_ = Vector2D{.0f, .0f};
    acceleration_ = Vector2D{.0f, .0f};
    width_ = params->width();
    height_ = params->height();
    textureId_ = params->textureId();
    currentFrame_ = currentRow_ = 1;
    numFrames_ = params->numFrame();
}
