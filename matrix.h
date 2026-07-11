/*
class matrix -> for moving objects
matrix = array of 16
// TODO: move sphere with matrix mult.

// TODO later: (for moving camera)
// transponieren
// determinante (google it, not full laplace)
// invertieren (1/det * transponierte matrix)
*/

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
    
    // define transformation matrices
    static matrix Translation(vec3 v) {
        return matrix(1, 0, 0, v.x(), 
                      0, 1, 0, v.y(), 
                      0, 0, 1, v.z(), 
                      0, 0, 0, 1);
    }

};  // end of class

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

// Matrix * vec4
// takes matrix, vec4, gives vec4
inline vec4 operator*(const matrix& m, vec4 v) {
    return vec4(m.e[0] * v.e[0] + m.e[1] * v.e[1] + m.e[2] * v.e[2] + m.e[3] * v.e[3],
                m.e[4] * v.e[0] + m.e[5] * v.e[1] + m.e[6] * v.e[2] + m.e[7] * v.e[3],
                m.e[8] * v.e[0] + m.e[9] * v.e[1] + m.e[10]* v.e[2] + m.e[11]* v.e[3],
                m.e[12]* v.e[0] + m.e[13]* v.e[1] + m.e[14]* v.e[2] + m.e[15]* v.e[3]);
}
/*
                                        v.e[0]
                                        v.e[1]
                                        v.e[2]
                                        v.e[3]

m.e[0]  m.e[1]  m.e[2]  m.e[3]           
m.e[4]  m.e[5]  m.e[6]  m.e[7]                       
m.e[8]  m.e[9]  m.e[10] m.e[11]         
m.e[12] m.e[13] m.e[14] m.e[15]         
*/

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
    m.e[4]  m.e[5]  m.e[6]  m.e[7]                       
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

inline matrix invert(const matrix& m) {
/*
Calculate inverse of an affine 4x4 matrix
m =
m.e[0]  m.e[1]  m.e[2]  m.e[3]
m.e[4]  m.e[5]  m.e[6]  m.e[7]                       
m.e[8]  m.e[9]  m.e[10] m.e[11]
m.e[12] m.e[13] m.e[14] m.e[15]

inverse(m) = A^-1   A^-1 * vektor
                0      1
A^-1 = 1/det(A) * adj(A)
*/
// calculate determinant of 3x3 matrix A
// det_A calculation tested, works.
float det_A = (m.e[0] * (m.e[5] * m.e[10] - m.e[6] * m.e[9]) -
               m.e[1] * (m.e[4] * m.e[10] - m.e[6] * m.e[8]) + 
               m.e[2] * (m.e[4] * m.e[9]  - m.e[5] * m.e[8]));
// calculate matrix A^-1
/*
a   b   c
d   e   f
g   h   i
A^-1 tested, works. 
*/
float a = 1 / det_A * (m.e[5] * m.e[10] - m.e[6] * m.e[9]);
float b = 1 / det_A * (m.e[2] * m.e[9]  - m.e[1] * m.e[10]);
float c = 1 / det_A * (m.e[1] * m.e[6]  - m.e[2] * m.e[5]);
float d = 1 / det_A * (m.e[6] * m.e[8]  - m.e[4] * m.e[10]);
float e = 1 / det_A * (m.e[0] * m.e[10] - m.e[2] * m.e[8]);
float f = 1 / det_A * (m.e[2] * m.e[4]  - m.e[0] * m.e[6]);
float g = 1 / det_A * (m.e[4] * m.e[9]  - m.e[5] * m.e[8]);
float h = 1 / det_A * (m.e[1] * m.e[8]  - m.e[0] * m.e[9]);
float i = 1 / det_A * (m.e[0] * m.e[5]  - m.e[1] * m.e[4]);

// calculate A^-1 * vektor
// vektor = x, y, z
float x = m.e[3];
float y = m.e[7];
float z = m.e[11];

float u = (-1) * (a * x + b * y + c * z);
float v = (-1) * (d * x + e * y + f * z);
float w = (-1) * (g * x + h * y + i * z);

matrix A = matrix(a, b, c, u,
                  d, e, f, v, 
                  g, h, i, w,
                  0, 0, 0, 1); 
return A;
}

#endif