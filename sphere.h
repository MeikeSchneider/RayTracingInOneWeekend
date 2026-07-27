#ifndef SPHERE_H
#define SPHERE_H

#include "simple_object.h"
#include "camera_old.h"

class sphere : public simple_object {
    // simple_object is base class for sphere, constructors of simple_objects are base conatructors
    public: 
        // basic constructor: calling the constructor from simple_object with no input
        sphere() : simple_object() {}

        sphere(vec3 position, float radius) {
            // constructor with position and radius, uses base constructor simple_object(vec3 translation, vec3 scale)
            // vec3 position -> vec3 translation 
            // float radius -> vec3 scale
            // constructor with translation and scale given
            vec3 scale = vec3(radius, radius, radius);
            vec3 translation = position;
            obj_to_world_matrix = matrix::Scale(scale) *  matrix::Translation(translation);
        }
    
        bool hit(const ray& r, interval ray_t, const matrix camera_to_world_matrix, hit_record& rec) const {
            // function that transformes ray into object space of sphere and checks for hits there
            // A_WtO matrix, inverse of world_to_obj_matrix of sphere
            matrix world_to_obj_matrix = invert(this->obj_to_world_matrix);
            // direction of ray transformed into object space of sphere
            vec3 direction_in_obj_space = vec4_to_vec3(world_to_obj_matrix * (camera_to_world_matrix * vec3_to_vec4(r.direction())));
            // same for origin
            vec3 origin_in_obj_space = vec4_to_vec3(world_to_obj_matrix * (camera_to_world_matrix * vec3_to_vec4(r.origin())));
            // calculate t with abc formula
            vec3 C = vec3(0, 0, 0);
            double a = dot(direction_in_obj_space, direction_in_obj_space);
            std::clog << "a, direction_in_obj_space = " << a << ", " << direction_in_obj_space << std::endl;
            double b = dot(direction_in_obj_space, (C - origin_in_obj_space));
            std::clog << "b, origin_in_obj_space = " << b << ", " << origin_in_obj_space << std::endl;
            double c = dot((C - origin_in_obj_space), (C - origin_in_obj_space)) - 1;
            std::clog << "c = " << c << std::endl;

            // calculate stuff under root(discriminat)
            auto discriminant = b * b - a * c;
            // check that discriminant is positiv
            if (discriminant < 0)
                return false;
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
            vec4 p_in_obj_space = vec3_to_vec4(origin_in_obj_space + t_in_obj_space * direction_in_obj_space);
            // transform p back into camera space
            vec3 p_in_cam_space = vec4_to_vec3(invert(camera_to_world_matrix) * (obj_to_world_matrix * p_in_obj_space));
            // recalculate t in cam space with p = Q + t * d ( with vars in cam space)
            double t_in_cam_space = (p_in_cam_space.x() - r.origin().x()) / r.direction().x();
            // set hit record
            rec.t = t_in_cam_space;
            rec.p = p_in_cam_space;
            // outward_normal is normalized p in camera space
            vec3 outward_normal = unit_vector(p_in_cam_space);
            rec.set_face_normal(r, outward_normal);
        }
};

#endif