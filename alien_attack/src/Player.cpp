#include "Player.h"
#include "InputHandler.h"
#include "LoaderParams.h"
#include "Game.h"

Player::Player() : ShooterObject{} {}

void Player::draw() { ShooterObject::draw(); }

void Player::update()
{
    auto game{TheGame::instance()};

    // If the level is complete then fly off the screen
    if (game->levelComplete())
    {
        if (position_.x() >= game->gameWidth())
            game->currentLevel(game->currentLevel() + 1);
        else
        {
            velocity_.x(3);
            velocity_.y(0);

            ShooterObject::update();
            handleAnimation();
        }
    }
    else
    {
        // if the player is not doing its death animation then update it normally
        if (!dying_)
        {
            velocity_.x(0);
            velocity_.y(0);

            handleInput();
            ShooterObject::update();
            handleAnimation();
        }
        else // if the player is doing the death animation
        {
            currentFrame_ = int((SDL_GetTicks64() / 100) % numFrame_);

            if (dyingCounter_ == dyingTime_)
                resurrect();

            ++dyingCounter_;
        }
    }

    currentFrame_ = static_cast<int>((SDL_GetTicks64() / 100) % 5);
    ShooterObject::update();
}

void Player::clean() {}

void Player::handleInput()
{
    auto target{TheInputHandler::instance()->mousePosition()};
    velocity_ = *target - position_;
    velocity_ /= 50;
}

void Player::resurrect()
{
    auto game{TheGame::instance()};
    game->playerLives(game->playerLives() - 1);

    position_.x(10);
    position_.y(200);
    dying_ = false;

    textureId_ = "player";

    currentFrame_ = 0;
    numFrame_ = 5;
    width_ = 101;

    height_ = 41;

    dyingCounter_ = 0;
    invulnerable_ = true;
}

void Player::handleAnimation()
{
    // If the player is invulnerable and that state has finished, set values back.
    if (invulnerable_ && invulnerableTime_ == invulnerableCounter_)
    {
        invulnerable_ = false;
        invulnerableCounter_ = 0;
        alpha_ = 255;
    }
    else // Otherwise, flash the alpha on and off.
    {
        if (alpha_ == 255)
            alpha_ = 0;
        else
            alpha_ = 255;
    }

    ++invulnerableCounter_;

    // If the player is not dead thenwe can change the angle with the velocity
    // to give the impression of a moving helicopter
    if (!dead_)
    {
        if (velocity_.x() < 0)
            angle_ = -10.;
        else if (velocity_.x() > 0)
            angle_ = 10.;
        else
            angle_ = 0.;
    }

    currentFrame_ = int((SDL_GetTicks64() / 100) % numFrame_);
}

void Player::load(const std::unique_ptr<LoaderParams> &params)
{
    ShooterObject::load(params);
}

std::string Player::type() const
{
    return "Player";
}
