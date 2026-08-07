#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "simple_object.h"

class triangle : public simple_object {
    public:
    // getter functions for vertex variables
    vec3 get_a() { return vertex_a; }
    vec3 get_b() { return vertex_b; }
    vec3 get_c() { return vertex_c; }

    // constructors
    // basic constructor: sets a, b, c
    // object_to_world_matrix is identity matrix, set by simple object base constructor
    triangle(vec3 a, vec3 b, vec3 c) : simple_object(), vertex_a(a), vertex_b(b), vertex_c(c) {}

    // constructor with a, b, c, translation given. Sets a, b, c.
    // object_to_world_matrix is set by base constructor using the translation
    triangle(vec3 a, vec3 b, vec3 c, vec3 translation
        ) : simple_object(translation), vertex_a(a), vertex_b(b), vertex_c(c) {}

    // constructor with a, b, c, translation, scale given. Sets a, b, c.
    // object_to_world_matrix is set by base constructor using translation, scale
    triangle(vec3 a, vec3 b, vec3 c, vec3 translation, vec3 scale
        ) : simple_object(translation, scale), vertex_a(a), vertex_b(b), vertex_c(c) {}

    // constructor with a, b, c, translation, scale, rotations given. Sets a, b, c.
    // object_to_world_matrix is set by base constructor using translation, scale, rotations
    triangle(vec3 a, vec3 b, vec3 c, vec3 translation, vec3 scale, float xRotation, float yRotation, float zRotation
        ) : simple_object(translation, scale, xRotation, yRotation, zRotation), vertex_a(a), vertex_b(b), vertex_c(c) {}


    // hit function
    bool hit(const ray& r, interval ray_t, const matrix camera_to_world_matrix, hit_record& rec) const override {
        // test if a ray hits the triangle
        // epsilon defined to account for floating point errors
        constexpr float epsilon = std::numeric_limits<float>::epsilon();

        // transform the triangle vertices into camera space
        matrix obj_to_cam_matrix = invert(camera_to_world_matrix) * obj_to_world_matrix;
        vec3 a_in_cam_space = vec4_to_vec3(obj_to_cam_matrix * vec3_to_vec4(vertex_a));
        vec3 b_in_cam_space = vec4_to_vec3(obj_to_cam_matrix * vec3_to_vec4(vertex_b));
        vec3 c_in_cam_space = vec4_to_vec3(obj_to_cam_matrix * vec3_to_vec4(vertex_c));
        // next, get the normal vector of the plane, the triangle is in
        // by getting the cross (Kreuzprodukt) of the vector from a to b and the vector from a to c
        // this vector is orthogonal to every point of the plane
        vec3 triangle_plane_normal = cross((b_in_cam_space - a_in_cam_space), (c_in_cam_space - b_in_cam_space));
        
        // next, check that ray and plane are not paralell
        // by checking that the dot product of the plane normal and the vector from the ray origin
        // to an arbitrary point of the plane (here it's a) is not 0
        // the absolute value is used because the sign doesn't matter, epsilon is used to account for floating point error
        // if (std::abs(dot(triangle_plane_normal, (vertex_a - r.direction()))) > epsilon) {
        if (std::abs(dot(triangle_plane_normal, r.direction())) > epsilon) {
            // next, calculate t (the position on the ray where the ray intersects the plane)
            double upper_fraq = dot(triangle_plane_normal, (a_in_cam_space - r.origin()));
            double lower_fraq = dot(r.direction(), triangle_plane_normal);
            double t = upper_fraq / lower_fraq;
            // std::clog << "t = " << t << std::endl;
            // if t is negative or 0, the intersection will be behind or at the ray origin and sould be discarded
            if (t < epsilon) {return false;}

            // calculate the intersection point of ray and plane
            // by putting t into the def for a ray = (ray.origin + t * ray.direction)
            vec3 intersection = r.origin() + t * r.direction();
            // std::clog << "intersection = " << intersection << std::endl;
            // paralell test, t and intersection point work for the example

            // check if intersection is inside the triangle
            /* apparently it doesn't work with dot product, instead cross product is needed
            double dot_1 = dot(intersection - vertex_a, intersection - vertex_b);
            std::clog << "dot_1 = " << dot_1 << std::endl;
            double dot_2 = dot(intersection - vertex_b, intersection - vertex_c);
            std::clog << "dot_2 = " << dot_2 << std::endl;
            double dot_3 = dot(intersection - vertex_c, intersection - vertex_a);
            std::clog << "dot_3 = " << dot_3 << std::endl;

            std::clog << "epsilon = " << epsilon << std::endl;
            if ((dot_1 > 0) && (dot_2 > 0) && (dot_3 > 0)) {
                std::clog << "intersection not in triangle" << std::endl;
                return false;
            } else {return true;}
            */
            
            // calculate the vectors from the vertices to the intersection point
            vec3 p_a = intersection - a_in_cam_space;
            vec3 p_b = intersection - b_in_cam_space;
            vec3 p_c = intersection - c_in_cam_space;
            // calculate the edge vectors
            vec3 edge_ab = b_in_cam_space - a_in_cam_space;
            vec3 edge_ac = c_in_cam_space - a_in_cam_space;
            vec3 edge_bc = c_in_cam_space - b_in_cam_space;
            vec3 edge_ca = a_in_cam_space - c_in_cam_space;
            // calculate the cross products
            vec3 cross_1 = cross(edge_ab, p_a);
            vec3 cross_2 = cross(edge_bc, p_b);
            vec3 cross_3 = cross(edge_ca, p_c);
            // check that all cross products point in the same direction as the triangle normal
            // if (dot(cross_1, cross_2) >= 0 && dot(cross_2, cross_3) >= 0) {
            if (dot(cross_1, triangle_plane_normal) >= 0 && dot(cross_2, triangle_plane_normal) >= 0 && dot(cross_3, triangle_plane_normal) >= 0) {
                // set hit record
                rec.t = t;
                rec.p = intersection;
                vec3 outward_normal = unit_vector(cross(edge_ab, edge_ac));
                rec.set_face_normal(r, outward_normal);
                return true; // The point is inside the triangle!
            } else {return false;}
        }
        else { return false; }
    }

    private:
    // three corners (vertices) of triangle
    vec3 vertex_a;
    vec3 vertex_b;
    vec3 vertex_c;
};
#endif