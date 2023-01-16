#include "ScrollingBackground.h"
#include "Game.h"
#include "TextureManager.h"
#include "LoaderParams.h"

ScrollingBackground::ScrollingBackground()
    : ShooterObject{}
    , count_{0}
    , maxCount_{0}
{
}

void ScrollingBackground::draw()
{
    SDL_RenderCopyEx(
        TheGame::instance()->renderer(), 
        TheTextureManager::instance()->textureMap()[textureId_], 
        &srcRec1,
        &dstRec1,
        0,
        nullptr,
        SDL_FLIP_NONE
    );

    SDL_RenderCopyEx(
        TheGame::instance()->renderer(), 
        TheTextureManager::instance()->textureMap()[textureId_], 
        &srcRec2,
        &dstRec2,
        0,
        nullptr,
        SDL_FLIP_NONE
    );
}

void ScrollingBackground::update()
{
    if(count_ == maxCount_)
    {
        // make first rectangle smaller
        srcRec1.x += scrollSpeed_;
        srcRec1.w -= scrollSpeed_;
        dstRec1.w -= scrollSpeed_;
        
        // make second rectangle bigger
        srcRec2.w += scrollSpeed_;
        dstRec2.w += scrollSpeed_;
        dstRec2.x -= scrollSpeed_;
        
        // reset and start again
        if(dstRec2.w >= width_)
        {
            srcRec1.x = 0;
            dstRec1.x = position_.x();
            srcRec1.y = 0;
            dstRec1.y = position_.y();
            
            srcRec1.w = dstRec1.w = srcRec2Width = dstRec1Width = width_;
            srcRec1.h = dstRec1.h = height_;
            
            srcRec2.x = 0;
            dstRec2.x = position_.x() + width_;
            srcRec2.y = 0;
            dstRec2.y = position_.y();
            
            srcRec2.w = dstRec2.w = srcRec2Width = dstRec2Width = 0;
            srcRec2.h = dstRec2.h = height_;
        }
        count_ = 0;
    }
    
    count_++;
}

void ScrollingBackground::clean()
{
    ShooterObject::clean();
}

void ScrollingBackground::load(const std::unique_ptr<LoaderParams> &params)
{
    ShooterObject::load(std::move(params));
    scrollSpeed_ = 1;

    srcRec1.x = 0;
    dstRec1.x = position_.x();
    srcRec1.y = 0;
    dstRec1.y = position_.y();

    srcRec1.w = dstRec1.w = srcRec1Width = dstRec1Width = width_;
    srcRec1.h = dstRec1.h = height_;

    srcRec2.x = 0;
    dstRec2.x = position_.x() + width_;
    srcRec2.y = 0;
    dstRec2.y = position_.y();

    srcRec2.w = dstRec2.w = srcRec2Width = dstRec2Width = 0;
    srcRec2.h = dstRec2.h = height_;    
}
