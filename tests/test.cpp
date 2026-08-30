#include <iostream>
#include "../math/interval.h"

void test_vec3();
void test_vec4();
void test_matrix();
void test_color();
void test_simple_obj();
void test_sphere();
void test_camera();
void test_triangle();
void test_triangle_hit();
void test_triangle_mesh();
void test_mesh_hit();
void test_obj_loader();

int main() {
    std::cout << "Testing vec3... "; test_vec3();

    std::cout << "Testing vec4... "; test_vec4();

    std::cout << "Testing matrix... "; test_matrix();

    std::cout << "Testing color... "; test_color();

    std::cout << "Testing simple_obj... "; test_simple_obj();

    std::cout << "Testing camera...\n"; test_camera();

    std::cout << "Testing sphere... "; test_sphere();

    std::cout << "Testing triangle... ";
    test_triangle();
    test_triangle_hit();

    std::cout << "Testing triangle mesh... ";
    test_triangle_mesh();
    test_mesh_hit();

    std::cout << "Testing object loader...\n"; test_obj_loader();


    std::cout << "\nAll tests passed!\n";
    return 0;
}