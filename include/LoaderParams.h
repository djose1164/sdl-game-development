#ifndef LOADER_PARAMS_H
#define LOADER_PARAMS_H

#include <string>

class LoaderParams
{
public:
    LoaderParams(int x, int y, int width, int height, std::string textureId);
    LoaderParams(int x, int y, int width, int height, std::string textureId, int numFrame);

    int x() const;
    int y() const;

    int width() const;
    int height() const;

    const std::string &textureId() const;

    int numFrame() const;

private:
    int x_;
    int y_;

    int width_;
    int height_;

    std::string textureId_;

    int numFrame_;
};

#endif //LOADER_PARAMS_H
