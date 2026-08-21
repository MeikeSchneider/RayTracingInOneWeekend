#include "../math/vec4.h"
#include <cassert>

// tests new functionality: transform 3d vector to 4d vector, 3d diretion to 4d, 4d to 3d
void test_vec4() {
    vec3 u = vec3(1, 2, 3);
    vec4 u_converted = pos3_to_vec4(u);
    assert(u_converted == vec4(1, 2, 3, 1));

    vec4 u_converted_2 = dir3_to_vec4(u);
    assert(u_converted_2 == vec4(1, 2, 3, 0));
    
    vec4 v = vec4(3, 6, 9, 2);
    vec3 v_converted = vec4_to_vec3(v);
    assert(v_converted == vec3(v.x()/v.w(), 3, v.z()/v.w()));
}
