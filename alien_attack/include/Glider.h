#ifndef GLIDER_H
#define GLIDER_H

#include "Enemy.h"

class Glider : public Enemy
{
public:
    Glider();

    virtual ~Glider() {}

    void load(const std::unique_ptr<LoaderParams> &params) override;

    void collision() override;

    void update() override;

private:
    int maxHeight_;
    int minHeight_;
    int gap_;
};

#endif //GLIDER_H
