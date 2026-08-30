#include <iostream>
#include "../math/interval.h"

void test_vec3();
void test_vec4();
void test_matrix();
void test_color();
void test_simple_obj();
void test_sphere();
void test_camera();

int main() {
    std::cout << "Testing vec3...\n";
    test_vec3();

    std::cout << "Testing vec4...\n";
    test_vec4();

    std::cout << "Testing matrix...\n";
    test_matrix();

    std::cout << "Testing color...\n";
    test_color();

    std::cout << "Testing simple_obj...\n";
    test_simple_obj();

    std::cout << "Testing sphere...\n";
    test_sphere();

    std::cout << "Testing camera...\n";
    test_camera();


    std::cout << "\nAll tests passed!\n";
    return 0;
}