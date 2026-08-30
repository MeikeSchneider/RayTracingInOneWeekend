#include <cassert>
#include "../scene/camera.h"

void test_camera() {
    // test basic constructor
    camera c = camera();
    matrix m = matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    assert(c.obj_to_world_matrix == m);
    
    // test constructor with pos given
    c = camera(vec3(1, 2, 3));
    m = matrix(1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 3, 0, 0, 0, 1);
    assert(c.obj_to_world_matrix == m);
    
    // test constructor with just rotation given
    c = camera(90, 0, 0);
    m = matrix();
    m = m.XRotation(90);
    assert(c.obj_to_world_matrix == m);
    
    // test constructor with pos and rotation given
    c = camera(vec3(1, 2, 3), 90, 0, 0);
    m = matrix();
    m = m.Translation(vec3(1, 2, 3)) * m.XRotation(90);
    assert(c.obj_to_world_matrix == m);
}