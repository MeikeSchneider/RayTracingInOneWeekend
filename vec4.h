#ifndef VEC4_H
#define VEC4_H

#include <cmath>
#include <iostream>

#include "vec3.h"

// handles homogeneous coordinates
class vec4 {
  public:
    // array of lenght 4
    double e[4];

    // empty constructor: sets all values to 0
    // if no vector values are given at making of the object, put 0s into vector, 1 at last pos
    vec4() : e{0, 0, 0, 1} {}
    /*
    write e0, e1, e2 into array e
    if values for the vector are given, these are put into the vector by constructor
    uses carthesian coordinates
    */
    vec4(double e0, double e1, double e2, double e3) : e{e0, e1, e2, e3} {}  // this like this, this but it inputs a list

    // functions to return corresponding number in array
    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }
    double w() const { return e[3]; }

    // define operators
    vec4 operator-() const { return vec4(-e[0], -e[1], -e[2], -e[3]); } // inverts numbers
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    vec4& operator+=(const vec4& v) {
        // self += v
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        e[3] += v.e[3];
        return *this; // after adding v to self, return self
    }

    // mutliply self with a scalar t
    vec4& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        e[3] *= t;
        return *this;
    }

    // same with divide (just use inverted multiply)
    vec4& operator/=(double t) {
        return *this *= 1/t;
    }

    double length() const {
        // lenght of vecor
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2] + e[3]*e[3];
    }
};

// point3 is just an alias for vec4, but useful for geometric clarity in the code.
using point4 = vec4;


// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec4& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2] << ' ' << v.e[3];
}

inline vec4 operator+(const vec4& u, const vec4& v) {
    return vec4(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2], u.e[3] + v.e[3]);
}

inline vec4 operator-(const vec4& u, const vec4& v) {
    return vec4(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2], u.e[3] - v.e[3]);
}

inline vec4 operator*(const vec4& u, const vec4& v) {
    return vec4(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2], u.e[3] * v.e[3]);
}

inline vec4 operator*(double t, const vec4& v) {
    return vec4(t*v.e[0], t*v.e[1], t*v.e[2], t*v.e[3]);
}

inline vec4 operator*(const vec4& v, double t) {
    return t * v;
}

inline vec4 operator/(const vec4& v, double t) {
    return (1/t) * v;
}

// dot product of two vectors u, v
inline double dot(const vec4& u, const vec4& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2]
         + u.e[3] * v.e[3];
}

// cross product of two 4d vectors u, v doesn't exist

// normalize lenght of vector
inline vec4 unit_vector(const vec4& v) {
    return v / v.length();
}

// takes 3d vector (carthesian), returns 4d vector (homogeneous)
inline vec4 vec3_to_vec4(const vec3& u) {
    return vec4(u.x(), u.y(), u.z(), 1);
}

// takes 4d vector (homogeneous vec) and returns 3d vec (carthesian)
inline vec3 vec4_to_vec3(const vec4& u) {
    if ( u.w() == 0 ) {
        return vec3(u.x(), u.y(), u.z());
    } else {
        return vec3(u.x() / u.w(), u.y() / u.w(), u.z() / u.w());
    }
}

#endif