#ifndef LOADER_PARAMS_H
#define LOADER_PARAMS_H

#include <string>

class LoaderParams
{
public:
    LoaderParams(int x, int y, int width, int height, std::string textureId);
    LoaderParams(
        int x, int y, int width, int height, 
        std::string textureId, int numFrame, 
        int callbackId = 0, int animSpeed = 0
    );

    int x() const;
    int y() const;

    int width() const;
    int height() const;

    const std::string &textureId() const;

    int animSpeed() const;
    int numFrame() const;

    int callbackId() const;

private:
    int x_;
    int y_;

    int width_;
    int height_;

    std::string textureId_;

    int numFrame_;

    int callbackId_;
    int animSpeed_;
};

#endif // LOADER_PARAMS_H
