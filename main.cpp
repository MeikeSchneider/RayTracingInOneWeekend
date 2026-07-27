#include "rtweekend.h"
#include "camera_old.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere_old.h"

#include "vec4.h"
#include "matrix.h"
#include "simple_object.h"
#include "sphere.h"
#include "objects_in_scene.h"

void test_vectors() {
    // tests different new functionality
    vec3 u = vec3(1, 2, 3);
    vec4 u_converted = vec3_to_vec4(u);
    vec4 v = vec4(3, 6, 9, 2);
    vec3 v_converted = vec4_to_vec3(v);
    std::clog << "u: " << u << ", u_converted: " << u_converted << std::endl;
    std::clog << "v: " << v << ", v_converted: " << v_converted << std::endl;
}

void test_matrices() {
    // test that empty constructor makes identity matrix
    matrix m = matrix();
    std::clog << "m: " << m << std::endl;
    // test that multiplication with a scalar works
    matrix n = matrix() * 5;
    std::clog << "n: " << n << std::endl;
    // test that constructor with values in it works
    matrix o = matrix(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    std::clog << "o: " << o << std::endl;
    o = o * 2;
    std::clog << "o*2: " << o << std::endl;
    // test that constructor with values in a list works
    double lst[16] = {3, 3, 3, 6, 6, 6, 9, 9, 9, 10, 11, 12, 13, 14, 15, 16};
    matrix p = matrix(lst);
    std::clog << "p: " << p << std::endl;
    // dividing by a scalar should work too
    p = p / 3;
    std::clog << "3*p: " << p << std::endl;
    // matrix multiplication
    matrix A = matrix(1, 2, 0, 1, 3, 0, 1, 2, 1, 1, 2, 0, 0, 2, 1, 1);
    matrix B = matrix(1, 0, 2, 1, 2, 1, 0, 1, 0, 2, 1, 2, 1, 0, 1, 0);
    matrix C = A * B;
    std::clog << "A*B: " << C << std::endl;
    // test matrix * vector 
    matrix D = matrix(1, 1, 1, 1, 
                       2, 2, 2, 2, 
                       3, 3, 3, 3, 
                       4, 4, 4, 4);
    vec4 v = vec4(1, 2, 3, 4);
    vec4 w = D * v;
    std::clog << "D*v: " << w << std::endl;
}

void test_matrix_invert() {
    // Tests for invert(matrix)
    matrix A = matrix(1, 0, 0, 5,
                      0, 1, 0, -3,
                      0, 0, 1, 8, 
                      0, 0, 0, 1);
    std::clog << "invert(A) = " << invert(A) << std::endl;

    // test for Translation matrix
    std::clog << "Translation matrix = " << matrix::Translation(vec3(1, 2, 3)) << std::endl;
    // test for Scale matrix
    std::clog << "Scale matrix = " << matrix::Scale(vec3(1, 2, 3)) << std::endl;
    // test for XRotation matrix
    std::clog << "XRotation matrix = " << matrix::XRotation(90) << std::endl;
    // test for YRotation matrix
    std::clog << "YRotation matrix = " << matrix::YRotation(90) << std::endl;
    // test for ZRotation matrix
    std::clog << "ZRotation matrix = " << matrix::ZRotation(90) << std::endl;
}

void test_simple_obj() {
    // test the empty constructor
    simple_object obj_1 = simple_object();
    std::clog << "object_1 = " << obj_1.obj_to_world_matrix << std::endl;
    // test constructor with scale and translation given
    simple_object obj_2 = simple_object(vec3(1, 2, 3), vec3(2, 2, 2), 0, 0, 0);
    std::clog << "object_2 = " << obj_2.obj_to_world_matrix << std::endl;
    // test the move function
    obj_1.move(vec3(3, 4, 5));
    std::clog << "object_1 = " << obj_1.obj_to_world_matrix << std::endl;
    obj_2.move(vec3(-1, -2, -3));
    std::clog << "object_2 = " << obj_2.obj_to_world_matrix << std::endl;
    // test the place function
    obj_1.place(vec3(3, 4, 5));
    std::clog << "object_1 = " << obj_1.obj_to_world_matrix << std::endl;
    obj_2.place(vec3(-1, -2, -3));
    std::clog << "object_2 = " << obj_2.obj_to_world_matrix << std::endl;
}

void test_sphere() {
    // test constructors
    sphere s = sphere();
    // std::clog << "s = " << s.obj_to_world_matrix << std::endl;
    sphere t = sphere(vec3(1, 2, 3), 5);
    // std::clog << "t = " << t.obj_to_world_matrix << std::endl;
    ray r = ray(vec3(0, 0, 0), vec3(1, 1, 1));
    hit_record rect;
    bool result = s.hit(r, interval(0, infinity), matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1), rect);
    std::clog << "result = " << result << std::endl;
}

void test_camera() {
    // test basic constructor
    camera b = camera();
    std::clog << "b = " << b.obj_to_world_matrix << std::endl;
    // test constructor with pos given
    camera c = camera(vec3(1, 2, 3));
    std::clog << "c = " << c.obj_to_world_matrix << std::endl;
    // test constructor with just rotation given
    camera d = camera(90, 0, 0);
    std::clog << "d = " << d.obj_to_world_matrix << std::endl;
    // test constructor with pos and rotation given
    camera e = camera(vec3(1, 2, 3), 90, 0, 0);
    std::clog << "e = " << e.obj_to_world_matrix << std::endl;
}

int main() {
    // hittable_list world;  // make list of hittable objects -> later: chnge to list of simple_objects
    // std::vector<simple_object> world; // TODO change to objects_in_scene world;
    objects_in_scene world;

    // add sphere and "floor" to hittables
    point3 sphere_center = point3(0, 0, -1); // later: use new sphere
    float radius = 0.5;
    // tutorial version: world.add(make_shared<sphere_old>(sphere_center, radius)); // make the sphere
    // tutorial version world.add(make_shared<sphere_old>(point3(0, -100.5, -1), 100));  // make green "floor" which is a sphere // same
    // second version: world.push_back(sphere(sphere_center, radius)); // TODO add: make it shared, change it to world.add(make_shared<sphere>(sphere_center, radius))
    // second version: world.push_back(sphere(point3(0, -100.5, -1), 100)); // TODO: same 
    
    world.add(make_shared<sphere>(sphere_center, radius));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
    // tutorial version: camera_old cam;  // create camera object // later: create new camera object
    camera cam;

    // later: change this in the new camera such that this is set by a constructor
    cam.aspect_ratio = 16.0 / 9.0;  // image width to image height is 16:9 
    cam.image_width  = 400;
    cam.samples_per_pixel = 100;  // anti-aliasing?

    // test_sphere();
    // test_camera();

    cam.render(world);
}
