#ifndef PLAYER_H
#define PLAYER_H

#include "ShooterObject.h"

class Player : public ShooterObject
{
public:
  Player();

  void draw() override;
  void update() override;
  void clean() override;

  void load(const std::unique_ptr<LoaderParams> &params) override;

  std::string type() const override;

private:
  void handleInput();

  // Bring the player back if there are lives left
  void resurrect();

  // Handle any animation for the player
  void handleAnimation();

  // Player can be invulnerable for a time
  bool invulnerable_;
  int invulnerableTime_;
  int invulnerableCounter_;
};

#endif // PLAYER_H
