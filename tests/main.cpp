#include <iostream>

void test_vec3();
void test_vec4();
void test_matrix();

int main() {
    std::cout << "Testing vec3...\n";
    test_vec3();

    std::cout << "Testing vec4...\n";
    test_vec4();

    std::cout << "Testing matrix...\n";
    test_matrix();


    std::cout << "\nAll tests passed!\n";
    return 0;
}