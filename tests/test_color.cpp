#include "../color.h"
#include <cassert>

void test_color() {
    // define variables
    // define results/ function calls
    // assert(functionResult == expectedResult)
    // test constructor
    color c(0, 0, 0);
    assert(c.r == 0);
    assert(c.g == 0);
    assert(c.b == 0);

    // test == operator
    color a(1, 2, 3);
    color b(1, 2, 3);
    bool res = a == b;
    assert(res == true);

    // test color + color
    color d = a + b;
    color e(2, 4, 6);
    assert(d == e);

    // test color + vec3, vec 3 + color
    vec3 v(1, 2, 3);
    d = v + e;
    color f = e + v;
    assert(color(3, 6, 9) == d);
    assert(color(3, 6, 9) == f);

    // test color - color, vec3 - color, color - vec3
    d = e - b;
    assert(color(1, 2, 3) == d);
    d = d - v;
    assert(color(0, 0, 0) == d);
    d = d - v;
    assert(color(-1, -2, -3) == d);

    // test color * color, number * color, color * number
    c = color(-1, 0, 2);
    d = color(2, 2, 2);
    assert(color(-2, 0, 4) == c * d);
    assert(color(-1.5, 0, 3) ==  c * 1.5);
    assert(color(-1.5, 0, 3) == 1.5 * c);
}
