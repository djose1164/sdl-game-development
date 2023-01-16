#ifndef ANIMATED_GRAPHIC_H
#define ANIMATED_GRAPHIC_H

#include "ShooterObject.h"

class LoaderParams;

class AnimatedGraphic : public ShooterObject
{
public:
    AnimatedGraphic();

    void update() override;
    void draw() override;
    void clean() override;

    void load(const std::unique_ptr<LoaderParams> &params) override;

private:
    int animSpeed_;
    int numFrames_;
};

#endif // ANIMATED_GRAPHIC_H
