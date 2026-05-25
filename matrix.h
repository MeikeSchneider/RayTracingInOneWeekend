// TODO: class matrix -> for moving sphere
// array of 16
// constructiors
// Matrix * matrix (* operator überladen)
// Matrix * vev4 (* operator überladen)
// vec * matrix not exist/useful
// Zb 5 * matrix (* überladen)
// zB matrix * 5 (same but seperate)

// later: (for moving camera)
// transponieren
// determinante (google it, not full laplace)
// invertieren (1/det * transponierte matrix)

#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>

#include "vec4.h"

class matrix {
    public:
    // array of lenght 16
    double e[16];
    // empty constructor: idendity matrix
    matrix() : e{1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0, 
                 0, 0, 0, 1} {}
    
    // constructor, with values given
    matrix(double e0,  double e1,  double e2,  double e3,
           double e4,  double e5,  double e6,  double e7,
           double e8,  double e9,  double e10, double e11,
           double e12, double e13, double e14, double e15) : e{
           e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15} {}
    
    // constructor, with list given
    matrix(double a[16]) : e{a[0],  a[1],  a[2],  a[3],
                             a[4],  a[5],  a[5],  a[7],
                             a[8],  a[9],  a[10], a[11],
                             a[12], a[13], a[14], a[15]} {}
};

// define operators
// matrix * scalar t
inline matrix operator*(const matrix& m, double t) {
    return matrix(m.e[0]  * t, m.e[1]  * t, m.e[2]  * t, m.e[3]  * t,
                  m.e[4]  * t, m.e[5]  * t, m.e[6]  * t, m.e[7]  * t,
                  m.e[8]  * t, m.e[9]  * t, m.e[10] * t, m.e[11] * t,
                  m.e[12] * t, m.e[13] * t, m.e[14] * t, m.e[15] * t);
}

// scalar t * matrix
inline matrix operator*(double t, const matrix& m) {
    return matrix(t * m.e[0],  t * m.e[1],  t * m.e[2],  t * m.e[3],
                  t * m.e[4],  t * m.e[5],  t * m.e[6],  t * m.e[7],
                  t * m.e[8],  t * m.e[9],  t * m.e[10], t * m.e[11],
                  t * m.e[12], t * m.e[13], t * m.e[14], t * m.e[15]);
}

// divide matrix by scalar t
inline matrix operator/(const matrix& m, double t){
    return (1/t) * m;
}

// matrix * matrix
inline matrix operator*(const matrix& m, const matrix& n) {
    return matrix(m.e[0]  * n.e[0] + m.e[1]  * n.e[4] + m.e[2]  * n.e[8]  + m.e[3]  * n.e[12],
                  m.e[0]  * n.e[1] + m.e[1]  * n.e[5] + m.e[2]  * n.e[9]  + m.e[3]  * n.e[13],
                  m.e[0]  * n.e[2] + m.e[1]  * n.e[6] + m.e[2]  * n.e[10] + m.e[3]  * n.e[14],
                  m.e[0]  * n.e[3] + m.e[1]  * n.e[7] + m.e[2]  * n.e[11] + m.e[3]  * n.e[15],

                  m.e[4]  * n.e[0] + m.e[5]  * n.e[4] + m.e[6]  * n.e[8]  + m.e[7]  * n.e[12],
                  m.e[4]  * n.e[1] + m.e[5]  * n.e[5] + m.e[6]  * n.e[9]  + m.e[7]  * n.e[13],
                  m.e[4]  * n.e[2] + m.e[5]  * n.e[6] + m.e[6]  * n.e[10] + m.e[7]  * n.e[14],
                  m.e[4]  * n.e[3] + m.e[5]  * n.e[7] + m.e[6]  * n.e[11] + m.e[7]  * n.e[15],
                
                  m.e[8]  * n.e[0] + m.e[9]  * n.e[4] + m.e[10] * n.e[8]  + m.e[11] * n.e[12],
                  m.e[8]  * n.e[1] + m.e[9]  * n.e[5] + m.e[10] * n.e[9]  + m.e[11] * n.e[13],
                  m.e[8]  * n.e[2] + m.e[9]  * n.e[6] + m.e[10] * n.e[10] + m.e[11] * n.e[14],
                  m.e[8]  * n.e[3] + m.e[9]  * n.e[7] + m.e[10] * n.e[11] + m.e[11] * n.e[15],

                  m.e[12] * n.e[0] + m.e[13] * n.e[4] + m.e[14] * n.e[8]  + m.e[15] * n.e[12],
                  m.e[12] * n.e[1] + m.e[13] * n.e[5] + m.e[14] * n.e[9]  + m.e[15] * n.e[13],
                  m.e[12] * n.e[2] + m.e[13] * n.e[6] + m.e[14] * n.e[10] + m.e[15] * n.e[14],
                  m.e[12] * n.e[3] + m.e[13] * n.e[7] + m.e[14] * n.e[11] + m.e[15] * n.e[15]);
    /*
                                    n.e[0]  n.e[1]  n.e[2]  n.e[3]
                                    n.e[4]  n.e[5]  n.e[6]  n.e[7]
                                    n.e[8]  n.e[9]  n.e[10] n.e[11]
                                    n.e[12] n.e[13] n.e[14] n.e[15]
    m.e[0]  m.e[1]  m.e[2]  m.e[3]
    m.e[4]  m.e[5]  m.e[6]  m.e[7]                       x
    m.e[8]  m.e[9]  m.e[10] m.e[11]
    m.e[12] m.e[13] m.e[14] m.e[15]
    */
}

// utility functions
// how to print out a matrix using iostream
inline std::ostream& operator<<(std::ostream& out, const matrix& m) {
    return out << m.e[0]  << ' ' << m.e[1]  << ' ' << m.e[2]  << ' ' << m.e[3]  <<
           ' ' << m.e[4]  << ' ' << m.e[5]  << ' ' << m.e[6]  << ' ' << m.e[7]  <<
           ' ' << m.e[8]  << ' ' << m.e[9]  << ' ' << m.e[10] << ' ' << m.e[11] <<
           ' ' << m.e[12] << ' ' << m.e[13] << ' ' << m.e[14] << ' ' << m.e[15];
}


#endif