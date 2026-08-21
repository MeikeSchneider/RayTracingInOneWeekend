#include "../math/matrix.h"
#include <cassert>


void test_matrix() {
    // test that empty constructor makes identity matrix
    matrix m = matrix();
    matrix id = matrix{1, 0, 0, 0,
                       0, 1, 0, 0,
                       0, 0, 1, 0, 
                       0, 0, 0, 1};
    assert(m == id);
    
    // test that multiplication with a scalar works
    matrix n = matrix() * 5;
    matrix ig = matrix{5, 0, 0, 0,
                       0, 5, 0, 0,
                       0, 0, 5, 0, 
                       0, 0, 0, 5};
    assert(n == ig);

    // test that constructor with values in it works
    matrix o = matrix(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    matrix ih = matrix{1, 2, 3, 4,
                       5, 6, 7, 8, 
                       9, 10, 11, 12, 
                       13, 14, 15, 16};
    assert(o == ih);
    o = o * 2;
    assert(o == ih * 2);
    
    // matrix multiplication
    matrix A = matrix(1, 2, 0, 1, 3, 0, 1, 2, 1, 1, 2, 0, 0, 2, 1, 1);
    matrix B = matrix(1, 0, 2, 1, 2, 1, 0, 1, 0, 2, 1, 2, 1, 0, 1, 0);
    matrix C = A * B;
    assert(A * B == C);

    // test matrix * vector 
    matrix D = matrix(1, 1, 1, 1, 
                      2, 2, 2, 2, 
                      3, 3, 3, 3, 
                      4, 4, 4, 4);
    vec4 v = vec4(1, 2, 3, 4);
    vec4 w = D * v;
    assert(w == vec4(10, 20, 30, 40));

    // Tests for invert(matrix)
    A = matrix(1, 0, 0, 5,
                0, 1, 0, -3,
                0, 0, 1, 8, 
                0, 0, 0, 1);
    matrix A_inv = matrix(1, 0, 0, -5, 0, 1, 0, 3, 0, 0, 1, -8, 0, 0, 0, 1);
    assert(invert(A) == A_inv);
    B = {7, 2, 1, 0,
        0, 3, -1, 0,
        -3, 4, -2, 0,
        0, 0, 0, 1};
    matrix B_inv = matrix(-2, 8, -5, -0, 3, -11, 7, -0, 9, -34, 21, -0, 0, 0, 0, 1);
    assert(invert(B) == B_inv);
}
