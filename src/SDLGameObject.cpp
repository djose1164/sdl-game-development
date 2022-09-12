#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams *params)
    : GameObject{params}
{
    x_ = params->x();
    y_ = params->y();
    width_ = params->width();
    height_ = params->height();
    textureId_ = params->textureId();

    currentFrame_ = currentRow_ = 1;
}

void SDLGameObject::draw()
{
    TextureManager::instance()->drawFrame(
        textureId_,
        x_,
        y_,
        width_,
        height_,
        currentRow_,
        currentFrame_,
        TheGame::instance()->renderer()
    );
}

void SDLGameObject::update()
{}

void SDLGameObject::clean()
{}
