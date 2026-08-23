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

// vertices.size() gives amount of triangles, triangles.size() gives number of vertices, so extra function needed
// when reading in triangles: triangles can be added with vertices.push_back(); 
// indices for triangles have to be calculated 
// vertices and triangles lists can be cleared using vertices.clear(); and triangles.clear();

class obj_loader {
    // class responsible for loading in .obj files, saving all of the information
    // and generating a triangle mesh out of it.
    // Later: also providing info for lighting, textures etc.

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
        // std::clog << "vertices_lst = " << vertices_lst << std::endl; // vertices_lst successfully set
        // std::clog << "normals_lst = " << normals_lst << std::endl;  // normals_lst successfully set
        // std::clog << "texCoords_lst = " << texCoords_lst << std::endl;
        // std::clog << "faces_lst = " << faces_lst << std::endl;

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

// function for generating a triangle mesh out of a .obj file
triangle_mesh make_triangle_mesh(const obj_loader& obj) {
    std::vector<vec3> vertices = obj.get_vertices_lst();
    // std::clog << "vertices = " << vertices << std::endl;
    std::vector<int> triangles;

    for (const face_vertex& current_vertex : obj.get_faces_lst()) {
        // std::clog << "faces = " << current_vertex << std::endl;
        triangles.push_back(current_vertex.vertex_index - 1);
    }
    if (triangles.size() % 3 != 0) { std::cerr << "File has stuff that's not triangles!" << std::endl; }
    // std::clog << "triangles = " << triangles << std::endl;
    triangle_mesh res = triangle_mesh(vertices, triangles);

    return res;
}

#endif