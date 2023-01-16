#ifndef PLAYER_H
#define PLAYER_H

#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:
  Player();

  void draw() override;
  void update() override;
  void clean() override;

  void load(const LoaderParams *params) override;

private:
  void handleInput();
};

#endif // PLAYER_H
