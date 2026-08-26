#ifndef SPHERE_H
#define SPHERE_H

#include "hittable_object.h"

class sphere : public hittable_object {
    // simple_object is base class for sphere, constructors of simple_objects are base conatructors
    public: 
        // basic constructor: calling the constructor from simple_object with no input
        sphere() : hittable_object() {}

        sphere(vec3 position, float radius) {
            // constructor with position and radius, uses base constructor simple_object(vec3 translation, vec3 scale)
            // vec3 position -> vec3 translation 
            // float radius -> vec3 scale
            // constructor with translation and scale given
            vec3 scale = vec3(radius, radius, radius);
            vec3 translation = position;
            obj_to_world_matrix = matrix::Translation(translation) *  matrix::Scale(scale);
        }
    
        bool hit(const ray& r, interval ray_t, const matrix camera_to_world_matrix, hit_record& rec) const override {
            // function that transformes ray into object space of sphere and checks for hits there
            // A_WtO matrix, inverse of world_to_obj_matrix of sphere
            matrix world_to_obj_matrix = invert(this->obj_to_world_matrix);
            // direction of ray transformed into object space of sphere
            vec4 dir = vec4(r.direction().x(), r.direction().y(), r.direction().z(), 0);
            vec3 direction_in_obj_space = vec4_to_vec3(world_to_obj_matrix * (camera_to_world_matrix * dir));
            // same for origin
            vec3 origin_in_obj_space = vec4_to_vec3(world_to_obj_matrix * (camera_to_world_matrix * pos3_to_vec4(r.origin())));
            // calculate t with abc formula
            vec3 C = vec3(0, 0, 0);
            double a = dot(direction_in_obj_space, direction_in_obj_space);
            double b = dot(direction_in_obj_space, (C - origin_in_obj_space));
            double c = dot((C - origin_in_obj_space), (C - origin_in_obj_space)) - 1;

            // calculate stuff under root(discriminat)
            auto discriminant = b * b - a * c;
            // check that discriminant is positiv
            if (discriminant < 0) { return false; }
            // calculate squareroot
            auto sqrtd = std::sqrt(discriminant);
            // find the nearest root that is positive
            // set variable by calculating whole formula with -
            auto t_in_obj_space = (b - sqrtd) / a;
            if (t_in_obj_space < 0) {
                // set variable by calculating whole formula with +
                auto t_in_obj_space = (b + sqrtd) / a;
                // if not usable solution was found: no hit
                if (t_in_obj_space < 0) {
                    return false;
                }
            }
            // calculate p = Q + t * d in object space
            vec3 p_3 = origin_in_obj_space + t_in_obj_space * direction_in_obj_space;
            vec4 p_in_obj_space = pos3_to_vec4(p_3);
            // transform p back into camera space
            vec3 p_in_cam_space = vec4_to_vec3(invert(camera_to_world_matrix) * (obj_to_world_matrix * p_in_obj_space));
            // recalculate t in cam space with p = Q + t * d ( with vars in cam space)
            double t_in_cam_space = (p_in_cam_space.x() - r.origin().x()) / r.direction().x();
            // set hit record
            rec.t = t_in_cam_space;
            rec.p = p_in_cam_space;
            // p in obj space, transformed as a direction into camera space
            // vec4 p_normal_in_obj_space = vec4(p_3.x(), p_3.y(), p_3.z(), 0);
            vec4 p_normal_in_obj_space = dir3_to_vec4(p_3);
            vec3 p_normal_in_cam_space = vec4_to_vec3(invert(camera_to_world_matrix) * (obj_to_world_matrix * p_normal_in_obj_space));
            // outward_normal is normalized p in camera space
            vec3 outward_normal = unit_vector(p_normal_in_cam_space);
            rec.set_face_normal(r, outward_normal);
            rec.mat = mat;

            return true;
        }
};

#endif