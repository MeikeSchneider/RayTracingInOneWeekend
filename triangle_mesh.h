#ifndef TRIANGLE_MESH_H
#define TRIANGLE_MESH_H

#include <vector>
#include "simple_object.h"

class triangle_mesh : public simple_object {
    public:
    // getters for private variable vertices
    std::vector<vec3> get_vertices() { return vertices; }
    // getters for private variable triangles
    std::vector<int> get_triangles() { return triangles; }
    
    // basic constructor that sets only vertices and triangles
    triangle_mesh(std::vector<vec3> vertex_list, std::vector<int> triangle_list
        ) : simple_object(), vertices(vertex_list), triangles(triangle_list) {}
    
    // constructor with translation
    triangle_mesh(std::vector<vec3> vertex_list, std::vector<int> triangle_list, vec3 translation
        ) : simple_object(translation), vertices(vertex_list), triangles(triangle_list) {}
    
    // constructor with translation and scale
    triangle_mesh(std::vector<vec3> vertex_list, std::vector<int> triangle_list, vec3 translation, vec3 scale
        ) : simple_object(translation, scale), vertices(vertex_list), triangles(triangle_list) {}

    // constructor with everything: translation, scale and rotation
    triangle_mesh(std::vector<vec3> vertex_list, std::vector<int> triangle_list, vec3 translation, vec3 scale, 
        float xRotation, float yRotation, float zRotation
        ) : simple_object(translation, scale, xRotation, yRotation, zRotation
        ), vertices(vertex_list), triangles(triangle_list) {}
    
    // utility functions:
    // vertices.size() gives amount of triangles, triangles.size() gives number of vertices, so extra function needed

    // add triangles to the vertices and the triangles lists
    // wenn man Dreiecke einließt, können diese Funktionen benutzt werden, um nach und nach Dreiecke zu vertices und triangles hinzuzufügen 
    void add_vertices(vec3 vertex) { vertices.push_back(vertex); }
    void add_triangles(int index_a, int index_b, int index_c) {
        triangles.push_back(index_a);
        triangles.push_back(index_b);
        triangles.push_back(index_c);
    }
    
    // clear the vertices and triangles lists
    void clear_vertices() { vertices.clear(); }
    void clear_triangles() { triangles.clear(); }

    // possible TODO: add a function to add lists of vertives/ triangles?

    // possible TODO: define how to print out the object? (if I can't print out a mesh while testing, it's needed)
    // inline std::ostream& operator<<(std::ostream& out, const vec4& v) {
    // return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2] << ' ' << v.e[3];
    // }

    // hit function
    // TODO

    private:
    // definition of triangle mesh:
    
    // list of coordinates (vec3) of vertices (Ecken) that stores the coordinates of the vertices of the triangles
    std::vector<vec3> vertices;
    // list of triangles that stores the indices of where in vertices the edges are
    std::vector<int> triangles;

};

// printing out the vertices list
inline std::ostream& operator<<(std::ostream& out, std::vector<vec3> vertices) {
    for (const auto i : vertices) {
        out << i << " ";
    }
    return out;
}

// printing out the triangles list
inline std::ostream& operator<<(std::ostream& out, std::vector<int> triangles) {
    for (const auto i : triangles) {
        out << i << " ";
    }
    return out;
}

#endif