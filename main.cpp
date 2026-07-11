#include "rtweekend.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#include "vec4.h"
#include "matrix.h"

void test() {
    // tests different new functionality
    /*
    vec3 u = vec3(1, 2, 3);
    vec4 u_converted = vec3_to_vec4(u);
    vec4 v = vec4(3, 6, 9, 2);
    vec3 v_converted = vec4_to_vec3(v);
    std::clog << "u: " << u << ", u_converted: " << u_converted << std::endl;
    std::clog << "v: " << v << ", v_converted: " << v_converted << std::endl;
    */
    // test that empty constructor makes identity matrix
    // matrix m = matrix();
    // std::clog << "m: " << m << std::endl;
    // test that multiplication with a scalar works
    // matrix n = matrix() * 5;
    // std::clog << "n: " << n << std::endl;
    // test that constructor with values in it works
    // matrix o = matrix(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    // std::clog << "o: " << o << std::endl;
    // o = o * 2;
    // std::clog << "o*2: " << o << std::endl;
    // test that constructor with values in a list works
    // double lst[16] = {3, 3, 3, 6, 6, 6, 9, 9, 9, 10, 11, 12, 13, 14, 15, 16};
    // matrix p = matrix(lst);
    // std::clog << "p: " << p << std::endl;
    // dividing by a scalar should work too
    // p = p / 3;
    // std::clog << "3*p: " << p << std::endl;
    // matrix multiplication
    // matrix A = matrix(1, 2, 0, 1, 3, 0, 1, 2, 1, 1, 2, 0, 0, 2, 1, 1);
    // matrix B = matrix(1, 0, 2, 1, 2, 1, 0, 1, 0, 2, 1, 2, 1, 0, 1, 0);
    // matrix C = A * B;
    // std::clog << "A*B: " << C << std::endl;
    // result: 6, 2, 3, 3, 5, 2, 8, 5, 3, 5, 4, 6, 5, 4, 3, 4
    // printed:6  2  3  3  5  2  9  5  3  5  4  6  5  4  2  4
    // matrix D = matrix(1, 1, 1, 1, 
    //                   2, 2, 2, 2, 
    //                   3, 3, 3, 3, 
    //                   4, 4, 4, 4);
    // vec4 v = vec4(1, 2, 3, 4);
    // vec4 w = D * v;
    // std::clog << "D*v: " << w << std::endl;
    // Tests for invert(matrix)
    matrix A = matrix(1, 0, 0, 5,
                      0, 1, 0, -3,
                      0, 0, 1, 8, 
                      0, 0, 0, 1);
    std::clog << "det(A)= " << invert(A) << std::endl;
}

int main() {
    hittable_list world;  // make list of hittable objects

    // add sphere and "floor" to hittables
    point3 sphere_center = point3(0, 0, -1);
    float radius = 0.5;
    world.add(make_shared<sphere>(sphere_center, radius));
    // world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));       // make the sphere
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));  // make green "floor" which is a sphere

    camera cam;  // create camera object

    cam.aspect_ratio = 16.0 / 9.0;  // image width to image height is 16:9
    cam.image_width  = 400;
    cam.samples_per_pixel = 100;  // anti-aliasing?

    test();

    cam.render(world);
}
