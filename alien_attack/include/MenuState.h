#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "GameState.h"

#include <vector>

class MenuState : public GameState
{
public:
    virtual ~MenuState() {}

protected:
    typedef void (*Callback)();

    virtual void setCallbacks(const std::vector<Callback> &callbacks) = 0;

    std::vector<Callback> callbacks_;
};

#endif // MENU_STATE_H
