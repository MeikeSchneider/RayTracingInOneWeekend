#include<cassert>
#include "../io/obj_loader.h"

void test_obj_loader() {
    obj_loader loader;
    loader.load("obj_files/cube.obj");
    std::vector<vec3> v_lst = {vec3(0, 0, 0), vec3(0, 1, 0), vec3(1, 1, 0), vec3(1, 0, 0), vec3(0, 0, 1), vec3(0, 1, 1), vec3(1, 1, 1), vec3(1, 0, 1)};
    std::vector<vec3> n_lst = {vec3(1, 0, 0), vec3(-1, 0, 0), vec3(0, 1, 0), vec3(0, -1, 0), vec3(0, 0, 1), vec3(0, 0, -1)};
    assert(loader.get_vertices_lst() == v_lst);
    assert(loader.get_normals_lst() == n_lst);
    // std::clog << "faces_lst = " << loader.get_faces_lst() << std::endl;

    triangle_mesh m = make_triangle_mesh(loader);
    assert(m.get_vertices() == v_lst);
    std::vector<int> t_lst = {2, 6, 7, 2, 7, 3, 0, 4, 5, 0, 5, 1, 6, 2, 1, 6, 1, 5, 3, 7, 4, 3, 4, 0, 7, 6, 5, 7, 5, 4, 2, 3, 0, 2, 0, 1};
    assert(m.get_triangles() == t_lst);
}