#include <cassert>
#include "../scene/hittable_obj/triangle_mesh.h"

void test_triangle_mesh() {
    // first constructor
    std::vector<vec3> vertex_list = {vec3(0, 0, 5), vec3(2, 0, 5), vec3(0, 2, 5)};
    std::vector<int> triangle_list = {0, 1, 2};
    triangle_mesh t = triangle_mesh(vertex_list, triangle_list);
    matrix m = matrix();
    assert(t.get_vertices() == vertex_list);
    assert(t.get_triangles() == triangle_list);
    assert(t.obj_to_world_matrix == m);

    // second constructor
    t = triangle_mesh(vertex_list, triangle_list, vec3(1, 2, 3));
    m = m.Translation(vec3(1, 2, 3));
    assert(t.obj_to_world_matrix == m);

    // third constructor
    t = triangle_mesh(vertex_list, triangle_list, vec3(1, 2, 3), vec3(4, 5, 6));
    m = m.Translation(vec3(1, 2, 3)) * m.Scale(vec3(4, 5, 6));
    assert(t.obj_to_world_matrix == m);
}

void test_mesh_hit() {
    // triangle gets hit by ray, t = 5, intersection point = (1, 1, 5)
    std::vector<vec3> vertex_list = {vec3(0, 0, 4), vec3(3, 0, 4), vec3(0, 3, 7)};
    std::vector<int> triangle_list = {0, 1, 2};
    triangle_mesh t = triangle_mesh(vertex_list, triangle_list);
    ray r = ray(vec3(1, 1, 0), vec3(0, 0, 1));
    matrix id = matrix();
    hit_record rect;
    bool res = t.hit(r, interval(0, infinity), id, rect);
    assert(res == 1);
    // std::clog << "Triangle mesh hit test successful" << std::endl;

    // triangle is paralell to ray, no t, no intersection point
    vertex_list = {vec3(0, 0, 4), vec3(0, 3, 4), vec3(0, 0, 7)};
    t = triangle_mesh(vertex_list, triangle_list);
    r = ray(vec3(1, 1, 0), vec3(0, 1, 0));
    res = t.hit(r, interval(0, infinity), id, rect);
    assert(res == 0);
    // std::clog << "Triangle paralell test successful" << std::endl;
    
    // triangle does not get hit by ray. Ray hits the plane but not the triangle, t = 5, intersection point = (4, 1, 5)
    vertex_list = {vec3(0, 0, 4), vec3(3, 0, 4), vec3(0, 3, 7)};
    t = triangle_mesh(vertex_list, triangle_list);
    r = ray(vec3(4, 1, 0), vec3(0, 0, 1));
    res = t.hit(r, interval(0, infinity), id, rect);
    assert(res == 0);
    // std::clog << "Triangle plane hit test successful" << std::endl;
    
    // triangle gets hit by ray. Ray hits the edge of the triangle, t = 5, intersection point = (1, 1, 5)
    vertex_list = {vec3(0, 0, 5), vec3(2, 0, 5), vec3(0, 2, 5)};
    t = triangle_mesh(vertex_list, triangle_list);
    r = ray(vec3(1, 1, 0), vec3(0, 0, 1));
    res = t.hit(r, interval(0, infinity), id, rect);
    assert(res == 1);
    // std::clog << "Triangle edge hit test 1 successful" << std::endl;
    // std::clog << "edge hit example: did the ray hit the plane? " << t.hit(r, interval(0, infinity), id, rect) << std::endl;

    // more triangles get hit by ray. Intersections: (2/3, 2/3, 2/3), 
    vertex_list = {vec3(2, 0, 0), vec3(0, 2, 0), vec3(0, 0, 2), // intersection: (2/3, 2/3, 2/3) 0,66666
                   vec3(5, 1, 1), vec3(1, 5, 1), vec3(1, 1, 5), // intersection: (7/3, 7/3, 7/3) 2,33333
                   vec3(8, 2, 2), vec3(2, 8, 2), vec3(2, 2, 8)};// intersection: (4, 4, 4)
    triangle_list = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    t = triangle_mesh(vertex_list, triangle_list);
    r = ray(vec3(0, 0, 0), vec3(1, 1, 1));
    res = t.hit(r, interval(0, infinity), id, rect);
    assert(res == 1);
    // std::clog << "Triangle edge hit test 2 successful" << std::endl;
    // std::clog << "edge hit example: did the ray hit the plane? " << t.hit(r, interval(0, infinity), id, rect) << std::endl;
}