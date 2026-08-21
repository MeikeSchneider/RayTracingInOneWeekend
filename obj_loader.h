#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <fstream>  // used for reading the file
#include <sstream>  // used for unpacking each line into it's components
#include "geometry/triangle_mesh.h"

// helping structs: small data structures to store specific things

// a structure to save the texture coordinates in something similar to a 2d vector
struct tex_coord {
    float u;
    float v;
};

// explain to iostream how to deal with tex_coord
std::ostream& operator<<(std::ostream& os, tex_coord& c) {
    os << c.u << "," << c.v << std::endl;
    return os;
}

// explain to iostream how to deal with list of tex_coord
std::ostream& operator<<(std::ostream& os, std::vector<tex_coord>& c) {
    for (const auto i : c) {
        os << i.u << ", " << i.v << std::endl;;
    }
    return os;
}

struct face_vertex{
    // a structure that holds the (possibly) 3 values that a face has, each index starts at 1
    int vertex_index = -1; // initializing it with -1 means, it's not been set.
    int texture_index = -1;
    int normal_index = -1;
};
// TODO: write functions for printing out face vertex and list of face vertex, like with the other struct

// vertices.size() gives amount of triangles, triangles.size() gives number of vertices, so extra function needed
// when reading in triangles: triangles can be added with vertices.push_back(); 
// indices for triangles have to be calculated 
// vertices and triangles lists can be cleared using vertices.clear(); and triangles.clear();

class obj_loader {
    // class responsible for loading in .obj files, saving all of the information
    // and generating a triangle mesh out of it.
    // Later: also providing info for lighting, textures etc.

    private:

    // list of 3d coordinates of the vertices
    std::vector<vec3> vertices_lst;
        
    // list of 3d coordinates of normal vectors
    std::vector<vec3> normals_lst;
        
    // list of 2d texture coordinates
    // how to use: texCoords_lst[0].u, texCoords_lst[0].v
    std::vector<tex_coord> texCoords_lst;

    // list of faces. Each face can have the three aspects defined in face_vertex
    std::vector<face_vertex> faces_lst;

    public:

    // program to read a file line by line using ifstream
    void load(const std::string& filename) {
        // open the file for reading
        std::ifstream input_file(filename);
        // if the file could not be opened, throw an error
        if (!input_file) {
            std::cerr << "Could not open file: " << filename << '\n';
            return;
        }
        // variable to store each line from the file
        std::string line;
        
        // read each line from the file
        while (std::getline(input_file, line)) {
            // fiter out comments
            if (line[0] == '#') { continue; }
            // unpack each line into components
            std::istringstream stream(line);
            std::string type;
            stream >> type;
            float x; float y; float z;
            // differenciate between different types
            if (type == "v") {
                // vertices
                stream >> x >> y >> z;
                vec3 vertex = vec3(x, y, z);
                vertices_lst.push_back(vertex);
            } else if (type == "vn") {
                // vertex normals
                stream >> x >> y >> z;
                vec3 normal = vec3(x, y, z);
                normals_lst.push_back(normal);
            } else if (type == "vt") {
                // texture coordinates
                stream >> x >> y;
                tex_coord res;
                res.u = x;
                res.v = y;
                texCoords_lst.push_back(res);
            } else if (type == "f") {
                // faces
                // does not work, TODO
                stream >> x >> y >> z;
                std::clog << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
            }
            else {continue; }
        } // end of while loop
        std::clog << "vertices_lst = " << vertices_lst << std::endl; // vertices_lst successfully set
        std::clog << "normals_lst = " << normals_lst << std::endl;  // normals_lst successfully set
        std::clog << "texCoords_lst = " << texCoords_lst << std::endl;

        /*
        // how to use: texCoords_lst[0].u, texCoords_lst[0].v
        std::vector<tex_coord> texCoords_lst;

        // list of faces. Each face can have the three aspects defined in face_vertex
        std::vector<face_vertex> faces_lst;
        */
        
        
        // close file after reading it
        input_file.close();
    }
};


#endif