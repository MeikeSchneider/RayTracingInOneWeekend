#include <cassert>
#include "../scene/simple_object.h"

void test_simple_obj() {
    // test the empty constructor
    simple_object obj_1 = simple_object();
    matrix m = matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    assert(obj_1.obj_to_world_matrix == m);
    
    // test constructor with scale and translation given
    simple_object obj_2 = simple_object(vec3(1, 2, 3), vec3(2, 2, 2), 0, 0, 0);
    m = matrix(2, 0, 0, 1, 0, 2, 0, 2, 0, 0, 2, 3, 0, 0, 0, 1);
    assert(obj_2.obj_to_world_matrix == m);
    
    // test the move function
    obj_1.move(vec3(3, 4, 5));
    m = matrix(1, 0, 0, 3, 0, 1, 0, 4, 0, 0, 1, 5, 0, 0, 0, 1);
    assert(obj_1.obj_to_world_matrix == m);
    
    obj_2.move(vec3(-1, -2, -3));
    m = matrix(2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1);
    assert(obj_2.obj_to_world_matrix == m);

    // test the place function
    obj_1.place(vec3(3, 4, 5));
    m = matrix(1, 0, 0, 3, 0, 1, 0, 4, 0, 0, 1, 5, 0, 0, 0, 1);
    assert(obj_1.obj_to_world_matrix == m);

    obj_2.place(vec3(-1, -2, -3));
    m = matrix(2, 0, 0, -1, 0, 2, 0, -2, 0, 0, 2, -3, 0, 0, 0, 1);
    assert(obj_2.obj_to_world_matrix == m);
}