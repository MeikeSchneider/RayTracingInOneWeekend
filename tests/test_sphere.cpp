#include <cassert>
#include "../scene/hittable_obj/sphere.h"

void test_sphere() {
    // test constructors
    sphere s = sphere();
    matrix m = matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    assert(s.obj_to_world_matrix == m);
    
    sphere t = sphere(vec3(1, 2, 3), 5);
    m = matrix(5, 0, 0, 1, 0, 5, 0, 2, 0, 0, 5, 3, 0, 0, 0, 1);
    assert(t.obj_to_world_matrix == m);
    
    ray r = ray(vec3(0, 0, 0), vec3(1, 1, 1));
    hit_record rect;
    bool result = s.hit(r, interval(0, infinity), matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1), rect);
    assert(result == 1);
}
