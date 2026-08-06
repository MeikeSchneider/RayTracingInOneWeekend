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
        // test that a ray hits the triangle
        // first, transform the triangle vertices into camera space
        matrix obj_to_cam_matrix = invert(camera_to_world_matrix) * obj_to_world_matrix;
        vec3 a_in_cam_space = vec4_to_vec3(obj_to_cam_matrix * vec3_to_vec4(vertex_a));
        vec3 b_in_cam_space = vec4_to_vec3(obj_to_cam_matrix * vec3_to_vec4(vertex_b));
        vec3 c_in_cam_space = vec4_to_vec3(obj_to_cam_matrix * vec3_to_vec4(vertex_c));
        // next, get the normal vector of the plane, the triangle is in
        // by getting the cross (Kreuzprodukt) of the vector from a to b and the vector from a to c
        // this vector is orthogonal to every point of the plane
        vec3 triangle_plane_normal = cross((vertex_b - vertex_a), (vertex_c - vertex_a));
        // next, check that ray and plane are not paralell
        // by checking that the dot product of the plane normal and the vector from the ray origin
        // to an arbitrary point of the plane (here it's a) is not 0
        if (dot(triangle_plane_normal, (vertex_a - r.direction())) != 0) {
            return true;
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