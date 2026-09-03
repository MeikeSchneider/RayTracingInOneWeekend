#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <fstream>  // used for reading the file
#include <sstream>  // used for unpacking each line into it's components
#include "../scene/hittable_obj/triangle_mesh.h"

// helping structs: small data structures to store specific things

// a structure to save the texture coordinates in something similar to a 2d vector
struct tex_coord {
    float u;
    float v;
};

// explain to iostream how to deal with tex_coord
inline std::ostream& operator<<(std::ostream& os, const tex_coord& c) {
    return os << "(" << c.u << "," << c.v << ")";
}

// explain to iostream how to deal with list of tex_coord
inline std::ostream& operator<<(std::ostream& os, const std::vector<tex_coord>& c) {
    for (const auto i : c) {
        os << "(" << i.u << ", " << i.v << ")";
    }
    return os;
}

struct face_vertex{
    // a structure that holds the (possibly) 3 values that a face has, each index starts at 1
    // initializing with -1 means, it's not been set.
    int vertex_index = -1;
    int texture_index = -1;
    int normal_index = -1;
};

// explain to iostream how to deal with face_vertex
inline std::ostream& operator<<(std::ostream& os, const face_vertex& f) {
    return os << "(" << f.vertex_index << "," << f.texture_index << "," << f.normal_index << ")";
}

// explain to iostream how to deal with list of face vertex
inline std::ostream& operator<<(std::ostream& os, const std::vector<face_vertex>& f) {
    for (const auto i : f) {
        os << "(" << i.vertex_index << ", " << i.texture_index << ", " << i.normal_index << ")";
    }
    return os;
}

// class responsible for loading in .obj files, saving all of the information
// and generating a triangle mesh out of it.
// Later: also providing info for lighting, textures etc.
class obj_loader {
    private:
    std::vector<vec3> vertices_lst; // list of 3d coordinates of the vertices, specified by v
    std::vector<vec3> normals_lst; // list of 3d coordinates of normal vectors, specified by vn
    std::vector<tex_coord> texCoords_lst; // list of 2d texture coords, specified by vt
    std::vector<face_vertex> faces_lst; // each face_vertex in the list has aspects of face_vertex, specifies by f

    public:
    // getter for private variables
    const std::vector<vec3>& get_vertices_lst() const { return vertices_lst; }
    const std::vector<vec3>& get_normals_lst() const { return normals_lst; }
    const std::vector<tex_coord>& get_texCoords_lst() const { return texCoords_lst; }
    const std::vector<face_vertex>& get_faces_lst() const { return faces_lst; }

    // function to read a file line by line using ifstream
    // fills vertices_lst, normals_lst, texCoords_lst, faces_lst.
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
                // std::clog << "tex_coords = " << res << std::endl;
                // std::clog << "texCoords_lst = " << texCoords_lst << std::endl;
            } else if (type == "f") {
                // faces
                // save all of the faces in a string of face_vertex
                std::vector<face_vertex> face;
                // save one entry/ one line as a string
                std::string vertex_data;
                // as long as there are entries in one face line, keep reading
                while (stream >> vertex_data) {
                    // a new stream for one face vertex: get vertexINdex = '1' etc out of 1/2/2
                    face_vertex face_vertex;
                    std::istringstream vertexStream(vertex_data);
                    // save the parts of one face line
                    std::string vertexIndex;
                    std::string texCoordIndex;
                    std::string normalIndex;
                    // read until the first '/' -> save first component in vertexIndex
                    std::getline(vertexStream, vertexIndex, '/');
                    // read until the second '/' -> save second component in texCoordIndex
                    std::getline(vertexStream, texCoordIndex, '/');
                    // read rest -> save third component in normalIndex
                    std::getline(vertexStream, normalIndex, '/');
                    // check that everything looks like it should
                    // std::clog << "vertexIndex = " << vertexIndex << std::endl;
                    // std::clog << "texCoordIndex = " << texCoordIndex << std::endl;
                    // std::clog << "normalIndex = " << normalIndex << std::endl;
                    // make vertexIndex into int, add it to the struct. stoi makes string to int
                    face_vertex.vertex_index = std::stoi(vertexIndex);
                    // if a texture coordinate exists, also make it into a string
                    if (!texCoordIndex.empty()) {
                        face_vertex.texture_index = std::stoi(texCoordIndex);
                    }
                    // if a normal exists, also make it into an int
                    if (!normalIndex.empty()) {
                        face_vertex.normal_index = std::stoi(normalIndex);
                    }
                    // add the finished built face_vertex to face
                    faces_lst.push_back(face_vertex);
                } // end of "f" while
                // faces_lst.push_back(face);
            } // end of "f" case
            else {continue; }
        } // end of big while loop
        
        // close file after reading it
        input_file.close();
    }
};

// function for generating a triangle mesh out of a .obj file
triangle_mesh make_triangle_mesh(const obj_loader& obj) {
    std::vector<vec3> vertices = obj.get_vertices_lst();
    std::vector<int> triangles;
    std::vector<vec3> normals = obj.get_normals_lst();
    std::vector<int> normal_indices;

    for (const face_vertex& current_vertex : obj.get_faces_lst()) {
        triangles.push_back(current_vertex.vertex_index - 1);
        if (current_vertex.normal_index != -1) { normal_indices.push_back(current_vertex.normal_index -1); }
    }
    if (triangles.size() % 3 != 0) { std::cerr << "File has stuff that's not triangles!" << std::endl; }
    
    if (!normals.empty() && !normal_indices.empty()) {
        return triangle_mesh(vertices, triangles, normals, normal_indices);
    }
    
    return triangle_mesh(vertices, triangles);
}

// same function, but with translation input
triangle_mesh make_triangle_mesh(const obj_loader& obj, vec3 translation) {
    std::vector<vec3> vertices = obj.get_vertices_lst();
    std::vector<int> triangles;
    std::vector<vec3> normals = obj.get_normals_lst();
    std::vector<int> normal_indices;

    for (const face_vertex& current_vertex : obj.get_faces_lst()) {
        triangles.push_back(current_vertex.vertex_index - 1);
        if (current_vertex.normal_index != -1) { normal_indices.push_back(current_vertex.normal_index -1); }
    }
    if (triangles.size() % 3 != 0) { std::cerr << "File has stuff that's not triangles!" << std::endl; }
    if (!normals.empty() && !normal_indices.empty()) {
        return triangle_mesh(vertices, triangles, normals, normal_indices, translation);
    }
    return triangle_mesh(vertices, triangles, translation);
}

// same function, but with translation and scale input
triangle_mesh make_triangle_mesh(const obj_loader& obj, vec3 translation, vec3 scale) {
    std::vector<vec3> vertices = obj.get_vertices_lst();
    std::vector<int> triangles;
    std::vector<vec3> normals = obj.get_normals_lst();
    std::vector<int> normal_indices;

    for (const face_vertex& current_vertex : obj.get_faces_lst()) {
        triangles.push_back(current_vertex.vertex_index - 1);
        if (current_vertex.normal_index != -1) { normal_indices.push_back(current_vertex.normal_index -1); }
    }
    if (triangles.size() % 3 != 0) { std::cerr << "File has stuff that's not triangles!" << std::endl; }
    if (!normals.empty() && !normal_indices.empty()) {
        return triangle_mesh(vertices, triangles, normals, normal_indices, translation, scale);
    }
    return triangle_mesh(vertices, triangles, translation, scale);
}

// same function, but with translation, scale, rotation input
triangle_mesh make_triangle_mesh(const obj_loader& obj, vec3 translation, vec3 scale, float xRot, float yRot, float zRot) {
    std::vector<vec3> vertices = obj.get_vertices_lst();
    std::vector<int> triangles;
    std::vector<vec3> normals = obj.get_normals_lst();
    std::vector<int> normal_indices;

    for (const face_vertex& current_vertex : obj.get_faces_lst()) {
        triangles.push_back(current_vertex.vertex_index - 1);
        if (current_vertex.normal_index != -1) { normal_indices.push_back(current_vertex.normal_index -1); }
    }
    if (triangles.size() % 3 != 0) { std::cerr << "File has stuff that's not triangles!" << std::endl; }
    if (!normals.empty() && !normal_indices.empty()) {
        return triangle_mesh(vertices, triangles, normals, normal_indices, translation, scale, xRot, yRot, zRot);
    }
    return triangle_mesh(vertices, triangles, translation, scale, xRot, yRot, zRot);
}

#endif