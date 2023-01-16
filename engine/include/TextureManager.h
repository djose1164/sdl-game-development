#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <SDL2/SDL.h>
#include <map>

class TextureManager
{
public:
    static TextureManager *instance();

    bool load(std::string filename, std::string id, SDL_Renderer *renderer);

    void draw(std::string id, int x, int y, int width, int height,
              SDL_Renderer *renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void drawFrame(std::string id, int x, int y, int width, int height,
                   int currentRow, int currentFrame, SDL_Renderer *renderer,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);

    void clearFromTextureMap(const std::string_view &id);

    void drawTile(std::string_view id, int margin, int spacing,
                  int x, int y, int width, int height, 
                  int curentRow, int currentFrame, SDL_Renderer *renderer);

private:
    TextureManager();
    ~TextureManager();

    std::map<std::string, SDL_Texture *> textureMap_;
    static TextureManager *instance_;
};

typedef TextureManager TheTextureManager;

#endif // TEXTURE_MANAGER_H
