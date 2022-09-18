#include "LoaderParams.h"

LoaderParams::LoaderParams(int x, int y, int width, int height, std::string textureId)
    : x_{x}
    , y_{y}
    , width_{width}
    , height_{height}
    , textureId_{textureId}
{}

LoaderParams::LoaderParams(int x, int y, int width, int height, std::string textureId, int numFrame)
    : x_{x}
    , y_{y}
    , width_{width}
    , height_{height}
    , textureId_{textureId}
    , numFrame_{numFrame}
{}

int LoaderParams::x() const
{
    return x_;
}
int LoaderParams::y() const
{
    return y_;
}

int LoaderParams::width() const
{
    return width_;
}
int LoaderParams::height() const
{
    return height_;
}

const std::string &LoaderParams::textureId() const
{
    return textureId_;
}

int LoaderParams::numFrame() const
{
    return numFrame_;
}
