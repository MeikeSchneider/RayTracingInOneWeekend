#ifndef COLOR_H
#define COLOR_H

#include "../math/vec3.h"
#include "vector"

// using color = vec3;  // color is just a vec3 with rgb values

// color "class" with variables and a basic constructor
// done to prevent that vec3 can be used for the file conversion calculations
struct color {
    double r;
    double g;
    double b;

    // ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}
    color() : r(0), g(0), b(0) {};
    color(double r, double g, double b) : r(r), g(g), b(b) {}
};

// explain to io stream how to deal with colors
inline std::ostream& operator<<(std::ostream& out, const color& c) {
    return out << c.r << ", " << c.g << ", " << c.b;
}

// explain to iostream how to deal with list of colors
inline std::ostream& operator<<(std::ostream& os, const std::vector<color>& c) {
    for (const auto i : c) {
        os << i.r << ", " << i.g << ", " << i.b;
    }
    return os;
}

inline bool operator==(color c1, color c2) {
    if (c1.r != c2.r) { return false; }
    else if (c1.g != c2.g) { return false; }
    else if (c1.b != c2.b) { return false; }
    else { return true; }
}

inline color operator+(color c1, color c2) {
    return color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

inline color operator+(vec3 v, color c2) {
    return color(v.x() + c2.r, v.y() + c2.g, v.z() + c2.b);
}

inline color operator+(color c2, vec3 v) {
    return color(c2.r + v.x(), c2.g + v.y(), c2.b + v.z());
}

inline color operator-(color c1, color c2) {
    return color(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
}

inline color operator-(vec3 v, color c2) {
    return color(v.x() - c2.r, v.y() - c2.g, v.z() - c2.b);
}

inline color operator-(color c2, vec3 v) {
    return color(c2.r - v.x(), c2.g - v.y(), c2.b - v.z());
}

inline color operator*(color c1, color c2) {
    return color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
}

inline color operator*(color c2, vec3 v) {
    return color(c2.r * v.x(), c2.g * v.y(), c2.b * v.z());
}

inline color operator*(vec3 v, color c2) {
    return color(v.x() * c2.r, v.y() * c2.g, v.z() * c2.b);
}

inline color operator*(double t, color c) {
    return color(t * c.r, t * c.g, t * c.b);
}

inline color operator*(color c, double t) {
    return t * c;
}

#endif