#ifndef VEC2D_H
#define VEC2D_H
#include <cmath>
#include "Constants.h"

struct Vec2D {
    double x, y;
    Vec2D(double xx, double yy) : x(xx), y(yy) {}

    Vec2D& normalize() {
        double length_squared = len2();
        if (length_squared > 0) {
            double inv_length = 1 / sqrt(length_squared);
            x *= inv_length, y *= inv_length;
        }
        return *this;
    }

    double len2() const { return x * x + y * y; }
    double len() const { return sqrt(len2()); }

    Vec2D operator * (const double& s) const { return Vec2D(x * s, y * s); } 
    Vec2D operator + (const Vec2D& v) const { return Vec2D(x + v.x, y + v.y); }
    Vec2D operator - (const Vec2D& v) const { return Vec2D(x - v.x, y - v.y); }
    Vec2D& operator += (const Vec2D& v) { x += v.x, y += v.y; return *this; }
    Vec2D& operator -= (const Vec2D& v) { x -= v.x, y -= v.y; return *this; }
};

#endif