#include "../math/vec3.h"
#include <cassert>

void test_vec3() {
    vec3 a(1, 2, 3);
    vec3 b(4, 5, 6);

    vec3 c = a + b;
    assert(c == vec3(5, 7, 9));
}