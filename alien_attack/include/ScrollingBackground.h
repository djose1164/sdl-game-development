#ifndef SCROLLING_BACKGROUND_H
#define SCROLLING_BACKGROUND_H

#include "ShooterObject.h"
#include "GameObjectFactory.h"

#include <SDL2/SDL.h>

class ScrollingBackground : public ShooterObject
{
public:
    ScrollingBackground();
    virtual ~ScrollingBackground() {}

    void draw() override;
    void update() override;
    void clean() override;

    virtual void load(const std::unique_ptr<LoaderParams> &params);

private:
    int scrollSpeed_;

    int count_;
    int maxCount_;

    SDL_Rect srcRec1;
    SDL_Rect srcRec2;

    SDL_Rect dstRec1;
    SDL_Rect dstRec2;
    
    int srcRec1Width;
    int srcRec2Width;

    int dstRec1Width;
    int dstRec2Width;
};

class ScrollingBackgroundCreator : public BaseCreator
{
public:
    virtual GameObject* createGameObject() const
    {
        return new ScrollingBackground();
    }
};

#endif // SCROLLING_BACKGROUND_H
