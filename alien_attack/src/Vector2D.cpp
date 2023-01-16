#include "Vector2D.h"

#include <cmath>

Vector2D::Vector2D()
    : x_{0}
    , y_{0}
{}

Vector2D::Vector2D(float x, float y)
    : x_{x}
    , y_{y}
{}

float Vector2D::x() const
{
    return x_;
}

void Vector2D::x(float x)
{
    x_ = x;
}

float Vector2D::y() const
{
    return y_;
}

void Vector2D::y(float y)
{
    y_ = y;
}

float Vector2D::length() const
{
    return std::sqrt(static_cast<double>(x_*x_ + y_*y_));
}

Vector2D Vector2D::operator+(const Vector2D &rhs) const
{
    return Vector2D(x() + rhs.x(), y() + rhs.y());
}

Vector2D Vector2D::operator+=(const Vector2D &rhs)
{
    x_ += rhs.x_;
    y_ += rhs.y_;

    return *this;
}

Vector2D Vector2D::operator*(const float scalar) const
{
    return Vector2D(x_ * scalar, y_ * scalar);
}

Vector2D Vector2D::operator*=(const float scalar)
{
    x_ *= scalar;
    y_ *= scalar;

    return *this;
}

Vector2D Vector2D::operator-(const Vector2D &rhs) const
{
    return Vector2D(x() - rhs.x(), y() - rhs.y());
}

Vector2D Vector2D::operator-=(const Vector2D &rhs)
{
    x_ -= rhs.x_;
    y_ -= rhs.y_;

    return *this;
}

Vector2D Vector2D::operator/(const float scalar) const
{
    return Vector2D(x_ / scalar, y_ / scalar);
}

Vector2D Vector2D::operator/=(const float scalar)
{
    x_ /= scalar;
    y_ /= scalar;

    return *this;
}
