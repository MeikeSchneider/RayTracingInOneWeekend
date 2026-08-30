#include <cassert>
#include "../scene/hittable_obj/triangle.h"

void test_triangle() {
    // test basic constructor
    triangle t = triangle(vec3(1, 1, 1), vec3(2, 2, 2), vec3(3, 3, 3));
    assert(t.get_a() == vec3(1, 1, 1));
    assert(t.get_b() == vec3(2, 2, 2));
    assert(t.get_c() == vec3(3, 3, 3));
    matrix m = matrix();
    assert(t.obj_to_world_matrix == m);
    
    // test constructor with pos
    t = triangle(vec3(0, 0, 0), vec3(-2, -2, -2), vec3(3, 3, 3), vec3(1, 2, 3));
    assert(t.get_a() == vec3(0, 0, 0));
    assert(t.get_b() == vec3(-2, -2, -2));
    assert(t.get_c() == vec3(3, 3, 3));
    m = m.Translation(vec3(1, 2, 3));
    assert(t.obj_to_world_matrix == m);
    
    // test constructor with pos, scale
    t = triangle(vec3(0.0, 0.5, 0), vec3(-2, -2, -2), vec3(3.2, 3.0, 3.1), vec3(1, 2, 3), vec3(2, 2, 2));
    assert(t.get_a() == vec3(0, 0.5, 0));
    assert(t.get_b() == vec3(-2, -2, -2));
    assert(t.get_c() == vec3(3.2, 3, 3.1));
    m = m.Translation(vec3(1, 2, 3)) * m.Scale(vec3(2, 2, 2));
    assert(t.obj_to_world_matrix == m);
}

void test_triangle_hit() {
    // test the hit function for the triangle
    
    // triangle gets hit by ray, t = 5, intersection point = (1, 1, 5)
    triangle t = triangle(vec3(0, 0, 4), vec3(3, 0, 4), vec3(0, 3, 7));
    ray r = ray(vec3(1, 1, 0), vec3(0, 0, 1));
    matrix id = matrix();
    hit_record rect;
    vec3 plane_normal = cross(t.get_b() - t.get_a(), t.get_c() - t.get_a());
    assert(plane_normal == vec3(0, -9, 9));
    double dot_product = dot(plane_normal, (t.get_a() - r.direction()));
    assert(dot_product == 27);
    bool res = t.hit(r, interval(0, infinity), id, rect);
    assert(res == 1);
    // std::clog << "Triangle hit test successful" << std::endl;
    
    // triangle is paralell to ray, no t, no intersection point
    t = triangle(vec3(0, 0, 4), vec3(0, 3, 4), vec3(0, 0, 7));
    r = ray(vec3(1, 1, 0), vec3(0, 1, 0));
    plane_normal = cross(t.get_b() - t.get_a(), t.get_c() - t.get_a());
    assert(plane_normal == vec3(9, 0, 0));
    dot_product = dot(plane_normal, (t.get_a() - r.direction()));
    assert(dot_product == 0);
    res = t.hit(r, interval(0, infinity), id, rect);
    assert(res == 0);
    // std::clog << "Triangle paralell test successful" << std::endl;
    
    // triangle does not get hit by ray. Ray hits the plane but not the triangle, t = 5, intersection point = (4, 1, 5)
    t = triangle(vec3(0, 0, 4), vec3(3, 0, 4), vec3(0, 3, 7));
    r = ray(vec3(4, 1, 0), vec3(0, 0, 1));
    plane_normal = cross(t.get_b() - t.get_a(), t.get_c() - t.get_a());
    assert(plane_normal == vec3(0, -9, 9));
    dot_product = dot(plane_normal, (t.get_a() - r.direction()));
    assert(dot_product == 27);
    res = t.hit(r, interval(0, infinity), id, rect);
    assert(res == 0);
    // std::clog << "Triangle plane hit test successful" << std::endl;
    
    // triangle gets hit by ray. Ray hits the edge of the triangle, t = 5, intersection point = (1, 1, 5)
    t = triangle(vec3(0, 0, 5), vec3(2, 0, 5), vec3(0, 2, 5));
    r = ray(vec3(1, 1, 0), vec3(0, 0, 1));
    plane_normal = cross(t.get_b() - t.get_a(), t.get_c() - t.get_a());
    assert(plane_normal == vec3(0, 0, 4));
    dot_product = dot(plane_normal, (t.get_a() - r.direction()));
    assert(dot_product == 16);
    res = t.hit(r, interval(0, infinity), id, rect);
    assert(res == 1);
    // std::clog << "Triangle edge hit test successful" << std::endl;
}
