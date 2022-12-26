#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
    Vector2D();
    Vector2D(float x, float y);

    float x() const;
    void x(float x);

    float y() const;
    void y(float y);

    float length() const;

    Vector2D operator+(const Vector2D &rhs) const;
    Vector2D operator+=(const Vector2D &rhs);

    Vector2D operator*(const float scalar) const;
    Vector2D operator*=(const float scalar);

    Vector2D operator*(const Vector2D &rhs) const;
    Vector2D operator*=(const Vector2D &rhs);

    Vector2D operator-(const Vector2D &rhs) const;
    Vector2D operator-=(const Vector2D &rhs);

    Vector2D operator/(const float scalar) const;
    Vector2D operator/=(const float scalar);

private:
    float x_;
    float y_;
};

#endif //VECTOR2D_H
