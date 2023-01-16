#ifndef SHOOTER_OBJECT_H
#define SHOOTER_OBJECT_H

#include "GameObject.h"
#include "Vector2D.h"

#include <string>

class LoaderParams;
class Vector2D;

class ShooterObject : public GameObject
{
public:
    virtual ~ShooterObject() {}

    void draw() override;
    void update() override;
    void clean() override;

    void load(const std::unique_ptr<LoaderParams> &params) override;

    const Vector2D &position() const;

    int width() const;
    int height() const;

    void collision() override;

    std::string type() const override;

protected:
    ShooterObject();

    void doDyingAnimation();

    int bulletFiringSpeed_;
    int bulletCounter_;

    int moveSpeed_;

    int dyingTime_;
    int dyingCounter_;

    bool playedDeathSound_;
};

#endif // SHOOTER_OBJECT_H
