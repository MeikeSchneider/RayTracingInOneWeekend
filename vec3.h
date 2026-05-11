#ifndef VEC3_H
#define VEC3_H

#include <cmath>
// #include <iostream>

class vec3 {
  public:
    // array of lenght 3
    double e[3];

    // empty constructor: sets all values to 0
    // if no vector values are given at making of the object, put 0s into vector
    vec3() : e{0, 0, 0} {}
    // write e0, e1, e2 into array e
    // if values for the vector are given, these are put into the vector by constructor
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    // functions to return corresponding number in array
    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    // define operators
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); } // inverts numbers
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3& v) {
        // self += v
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this; // after adding v to self, return self
    }

    // mutliply self with a scalar t
    vec3& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    // same with divide (just use inverted multiply)
    vec3& operator/=(double t) {
        return *this *= 1/t;
    }

    double length() const {
        // lenght of vecor
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;


// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

// dot product of two vectors u, v
inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

// cross product of two vectors u, v
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// normalize lenght of vector
inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

#endif