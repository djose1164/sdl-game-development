#include "TextureManager.h"

#include <SDL2/SDL_image.h>

TextureManager *TextureManager::instance_{nullptr};

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

TextureManager *TextureManager::instance()
{
    if (!instance_)
        instance_ = new TextureManager;

    return instance_;
}

bool TextureManager::load(std::string filename, std::string id, SDL_Renderer *renderer)
{
    auto surface{IMG_Load(filename.c_str())};
    if (!surface)
    {
        SDL_Log("Could not load image: %s", SDL_GetError());
        return false;
    }

    auto texture{SDL_CreateTextureFromSurface(renderer, surface)};
    SDL_FreeSurface(surface);

    if (!texture)
    {
        SDL_Log("Could not create texture fom surface: %s", SDL_GetError());
        return false;
    }
    // Everything went ok!
    textureMap[id] = texture;
    return true;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer *renderer, SDL_RendererFlip flip)
{
    SDL_Log("TextureManager::draw");
    SDL_Rect srcRec{
        .x = 0,
        .y = 0,
        .w = width,
        .h = height};

    auto dstRec{srcRec};
    dstRec.x = x;
    dstRec.y = y;

    SDL_RenderCopyEx(
        renderer,
        textureMap[id],
        &srcRec,
        &dstRec,
        .0,
        nullptr,
        flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *renderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRec;
    SDL_Rect dstRec;

    srcRec.x = width * currentFrame;
    srcRec.y = height * (currentRow - 1);
    srcRec.w = dstRec.w = width;
    srcRec.h = dstRec.h = height;
    dstRec.x = x;
    dstRec.y = y;

    SDL_RenderCopyEx(
        renderer,
        textureMap[id],
        &srcRec,
        &dstRec,
        .0,
        nullptr,
        flip
    );
}
    