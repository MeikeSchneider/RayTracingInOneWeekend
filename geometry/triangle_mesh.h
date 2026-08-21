#ifndef TRIANGLE_MESH_H
#define TRIANGLE_MESH_H

#include <vector>
#include "../simple_object.h"

class triangle_mesh : public simple_object {
    public:
    // getters for private variable vertices
    // use reference to avoid unneccessary copying
    const std::vector<vec3>& get_vertices() const { return vertices; }
    // old getter: std::vector<vec3> get_vertices() { return vertices; }
    // getters for private variable triangles
    const std::vector<int>& get_triangles() const { return triangles; }
    // std::vector<int> get_triangles() { return triangles; }
    
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

    // hit function: test for all triangles of the mesh if the ray hits it
    // Uses the Möller-Trumbore-algorithm, expanded for meshes
    bool hit(const ray& r, interval ray_t, const matrix camera_to_world_matrix, hit_record& rec) const override {
        // epsilon defined to account for floating point errors
        constexpr double epsilon = std::numeric_limits<double>::epsilon();

        // variables for temporary hit record
        double temp_t = ray_t.max;
        point3 temp_p;
        vec3 temp_outward_normal;
        
        // check that the size of triangles is divisible by 3
        // if (triangles.size() % 3 != 0) { return false; }
        
        // iterate through triangles in steps of size 3. Take the indices and look up the coordinates in vertices
        for (int i = 0; i < triangles.size(); i=i+3) {
            vec3 vertex_a = vertices[triangles[i]];
            vec3 vertex_b = vertices[triangles[i+1]];
            vec3 vertex_c = vertices[triangles[i+2]];

            matrix obj_to_cam_matrix = invert(camera_to_world_matrix) * obj_to_world_matrix;
            // transform the triangle vertices into camera space
            vec3 a_in_cam_space = vec4_to_vec3(obj_to_cam_matrix * pos3_to_vec4(vertex_a));
            vec3 b_in_cam_space = vec4_to_vec3(obj_to_cam_matrix * pos3_to_vec4(vertex_b));
            vec3 c_in_cam_space = vec4_to_vec3(obj_to_cam_matrix * pos3_to_vec4(vertex_c));

            // calculate edges AB, AC, BC
            vec3 edge_ab = b_in_cam_space - a_in_cam_space; // E1: A to B
            vec3 edge_ac = c_in_cam_space - a_in_cam_space; // E2: A to C
            vec3 edge_bc = c_in_cam_space - b_in_cam_space; // E3: B to C

            // get normal vector of triangle plane by calculating cross product (Kreuzprodukt) of E1 and E3
            // this vector is orthogonal to every point of the plane
            vec3 triangle_plane_normal = cross(edge_ab, edge_bc);

            // some helping vectors
            vec3 P = cross(r.direction(), edge_ac);
            vec3 T = r.origin() - a_in_cam_space;
            vec3 Q = cross(T, edge_ab);
            double det = dot(edge_ab, P);

            // check if ray and triangle plane are paralell
            if(std::abs(det) < epsilon) {continue;} // std::abs NOT abs!!!!
        
            // calculate u from the barycentric coordinates for a triangle:
            // any point P on a triangle is defined as P = a + u(b-a) + v(c-a)
            double u = (dot(T, P) / det);
            // check that u is not smaller than 0 or bigger than 1, otherwise hit outside triangle
            if (u < epsilon || u > 1) {continue;}

            // calculate v
            double v = (dot(r.direction(), Q)/ det);
            // check that v is not smaller than 0 or that u+v is bigger than 1, otherwise hit outside triangle
            if (v < epsilon || u+v > 1) {continue;}

            // calculate t (point on ray where the plane is hit)
            double t = (dot(edge_ac, Q) / det);
            // check that t is bigger than 0, so located after the ray origin, otherwise ignore hit
            if (t < epsilon) {continue;}

            // calculate intersection point by putting t into the def for a ray = (ray.origin + t * ray.direction)
            vec3 intersection = r.origin() + t * r.direction();
            // std::clog << "intersection = " << intersection << std::endl;
            
            // set temporary hit record if a smaller t > 0 is found -> an intersection closer to the camera
            if (t < temp_t && t > epsilon) {
                // std::clog << "wrote into temp hit record" << std::endl;
                temp_t = t; // t from ray equation, needed for insection calculation
                temp_p = intersection; // actual intersection point
                temp_outward_normal = unit_vector(triangle_plane_normal);
            }
        } // end of big for loop
        
        // set final hit record if something has been written in the temporary hit record
        // std::clog << "temp_t = " << temp_t << std::endl;
        if (temp_t < ray_t.max) {
            // std::clog << "wrote into final hit record" << std::endl;
            rec.t = temp_t;
            rec.p = temp_p;
            rec.set_face_normal(r, temp_outward_normal);
            return true; // The point is inside the triangle!
        }
        return false;
    }

    private:
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