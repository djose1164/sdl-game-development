#include "Glider.h"
#include "SoundManager.h"

Glider::Glider()
    : Enemy{}
    , maxHeight_{0}
    , minHeight_{0}
    , gap_{60}
{
    dyingTime_ = 25;
    health_ = 1;
    moveSpeed_ = 3;
}

void Glider::load(const std::unique_ptr<LoaderParams> &params)
{
    ShooterObject::load(std::move(params));

    velocity_.x(-moveSpeed_);
    velocity_.y(moveSpeed_/2);

    maxHeight_ = position_.y() + gap_;
    minHeight_ = position_.y() - gap_;
}

void Glider::collision()
{
    --health_;

    if (health_ != 0 && playedDeathSound_)
        return;
    
    TheSoundManager::instance()->playSound("explode", 0);

    textureId_ = "explosion";
    currentFrame_ = 0;
    numFrame_ = 9;
    width_ = height_ = 40;
    dying_ = true;
}

void Glider::update()
{
    if (dying_)
    {
        velocity_.x(0);
        velocity_.y(0);
        doDyingAnimation();
    }
    else if (position_.y() >= maxHeight_)
        velocity_.y(-moveSpeed_);
    else if (position_.y() <= minHeight_)
        velocity_.y(moveSpeed_);

    ShooterObject::update();
}
