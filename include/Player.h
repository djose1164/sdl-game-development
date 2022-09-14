#ifndef PLAYER_H
#define PLAYER_H

#include "SDLGameObject.h"

class Player : public SDLGameObject {
public:
  Player(const LoaderParams *params);

  virtual void draw() override;
  virtual void update() override;
  virtual void clean() override;

private:
  void handleInput();
};

#endif // PLAYER_H
