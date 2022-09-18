#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams *params)
    : GameObject{}
    , position_{float(params->x()), float(params->y())}
    , velocity_{.0f, .0f}
    , acceleration_{.0f, .0f}
{
    width_ = params->width();
    height_ = params->height();
    textureId_ = params->textureId();

    currentFrame_ = currentRow_ = 1;
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
            SDL_FLIP_HORIZONTAL
        );
    else
        TextureManager::instance()->drawFrame(
            textureId_,
            static_cast<Uint32>(position_.x()),
            static_cast<Uint32>(position_.y()),
            width_,
            height_,
            currentRow_,
            currentFrame_,
            TheGame::instance()->renderer()
        );

}

void SDLGameObject::update()
{
    velocity_ += acceleration_;
    position_ += velocity_;
}

void SDLGameObject::clean()
{}
