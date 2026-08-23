#ifndef SIMPLE_OBJECT_H
#define SIMPLE_OBJECT_H

#include "rtweekend.h"
#include "camera.h"
#include "hittable.h"

class simple_object {
    /*
    Class that defines a simple object
    Sphere and triangle will inherit from it
    All simple objects will be defined by matrices and can be moved/ 
    rotated/ etc. by transformation matrices
    */

    public:
        // Matrix always represents the transformation from object space to world space
        matrix obj_to_world_matrix;
        const vec3 get_pos() { return vec3(obj_to_world_matrix.e[3], obj_to_world_matrix.e[7], obj_to_world_matrix.e[11]); }
    
        // empty constructor: identity matrix
        simple_object() {
            obj_to_world_matrix = matrix(
            1, 0, 0, 0,
            0, 1, 0, 0, 
            0, 0, 1, 0,
            0, 0, 0, 1);
        }

        // constructor with translation
        simple_object(vec3 translation) {
            obj_to_world_matrix = matrix::Translation(translation);
        }

        // constructor with translation and scale given
        simple_object(vec3 translation, vec3 scale) {
            obj_to_world_matrix = matrix::Translation(translation) * matrix::Scale(scale);
        }

        /* 
        constructor, with all values given
        generates the matrices out of the values given, combines them into one matrix.
        order of operation: rotation: z * y * x
        everyting: scale * rotation * translation  */
        simple_object(vec3 translation, vec3 scale, float xRotation, float yRotation, float zRotation) {
            matrix rotation = matrix::ZRotation(zRotation) * (matrix::YRotation(yRotation) * matrix::XRotation(xRotation));
            obj_to_world_matrix = matrix::Translation(translation) * (rotation *  matrix::Scale(scale));
        } 
        
        // takes in a position that should be added to the current position, makes a translation matrix out of it
        // and multiplies that with the matrix
        void move(const vec3& position) {
            obj_to_world_matrix = matrix::Translation(position) * obj_to_world_matrix;
        }

        // takes in a pos where the object should be moved to, overwrites the enties of the matrix
        void place(const vec3& position) {
            obj_to_world_matrix.e[3]  = position.x();
            obj_to_world_matrix.e[7]  = position.y();
            obj_to_world_matrix.e[11] = position.z();
        }

        // hit function. Place holder for overwriting later, sets an object as not hittable as a standard
        virtual bool hit(const ray& r, interval ray_t, const matrix camera_to_world_matrix, hit_record& rec) const {
            std::clog << "called base function" << std::endl;
            return false;
        }
};

#endif