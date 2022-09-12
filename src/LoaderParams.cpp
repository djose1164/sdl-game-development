#include "LoaderParams.h"

LoaderParams::LoaderParams(int x, int y, int width, int height, std::string textureId)
    : x_{x}
    , y_{y}
    , width_{width}
    , height_{height}
    , textureId_{textureId}
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