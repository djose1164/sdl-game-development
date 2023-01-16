#include "ShooterObject.h"
#include "LoaderParams.h"
#include "TextureManager.h"
#include "Game.h"

ShooterObject::ShooterObject()
    : GameObject{}
{
}

void ShooterObject::doDyingAnimation()
{
    SDL_Log("dying..");
    scroll(TheGame::instance()->scrollSpeed());

    currentFrame_ = int(((SDL_GetTicks64() / (1'000 / 3))) % numFrame_);

    if (dyingCounter_ == dyingTime_)
        dead_ = true;
    ++dyingCounter_;
}

void ShooterObject::draw()
{
    TheTextureManager::instance()->drawFrame(
        textureId_,
        static_cast<Uint32>(position_.x()),
        static_cast<Uint32>(position_.y()),
        width_,
        height_,
        currentRow_,
        currentFrame_,
        TheGame::instance()->renderer(),
        angle_,
        alpha_
    );
}

void ShooterObject::update()
{
    velocity_ += acceleration_;
    position_ += velocity_;
}

void ShooterObject::clean()
{
}

const Vector2D &ShooterObject::position() const
{
    return position_;
}

int ShooterObject::width() const
{
    return width_;
}

int ShooterObject::height() const
{
    return height_;
}

void ShooterObject::collision()
{
}

void ShooterObject::load(const std::unique_ptr<LoaderParams> &params)
{
    position_ = Vector2D{float(params->x()), float(params->y())};
    velocity_ = Vector2D{.0f, .0f};
    acceleration_ = Vector2D{.0f, .0f};
    width_ = params->width();
    height_ = params->height();
    textureId_ = params->textureId();
    currentFrame_ = currentRow_ = 1;
    numFrame_ = params->numFrame();
    SDL_Log("[%s]: textureId_: %s", __func__, textureId_.c_str());
}

std::string ShooterObject::type() const
{
    return "ShooterObject";
}
