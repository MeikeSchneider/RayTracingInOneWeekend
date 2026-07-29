#ifndef SIMPLE_OBJECT_H
#define SIMPLE_OBJECT_H

#include "matrix.h"
#include "vec3.h"
#include "ray.h"
#include "interval.h"
#include "camera_old.h"
// #include "camera.h"

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
    
        simple_object() {obj_to_world_matrix = matrix(
            // empty constructor: identity matrix
            1, 0, 0, 0,
            0, 1, 0, 0, 
            0, 0, 1, 0,
            0, 0, 0, 1);
        }

        simple_object(vec3 translation, vec3 scale, float xRotation, float yRotation, float zRotation) {
            /* constructor, with all values given
            generates the matrices out of the values given, combines them into one matrix.
            order of operation:
            rotation: z * y * x
            everyting: scale * rotation * translation  */
            //DONE TODO
            matrix rotation = matrix::ZRotation(zRotation) * (matrix::YRotation(yRotation) * matrix::XRotation(xRotation));
            obj_to_world_matrix = matrix::Translation(translation) * (rotation *  matrix::Scale(scale));
        } 
        
        simple_object(vec3 translation, vec3 scale) {
            // constructor with translation and scale given
            // DONE TODO
            obj_to_world_matrix = matrix::Translation(translation) * matrix::Scale(scale);
        }
        
        void move(const vec3& position) {
            // takes in a position that should be added to the current position, makes a translation matrix out of it
            // and multiplies that with the matrix
            obj_to_world_matrix = matrix::Translation(position) * obj_to_world_matrix;
        }

        void place(const vec3& position) {
            // takes in a pos where the object should be moved to, overwrites the enties of the matrix
            obj_to_world_matrix.e[3]  = position.x();
            obj_to_world_matrix.e[7]  = position.y();
            obj_to_world_matrix.e[11] = position.z();
        }

        // bool hit(const ray& r, interval ray_t, const camera& cam, hit_record& rec) const {
        virtual bool hit(const ray& r, interval ray_t, const matrix camera_to_world_matrix, hit_record& rec) const {
            /*
            hit function. Place holder for overwriting later, sets an object as not hittable as a standard
            wenn es später Probleme gibt wegen inclusion kreis (camera includes simple object which includes camera)
            just give hit function the world_to_obj matrix instead of the whole camera 
            bool hit(const ray& r, interval ray_t, const camera_old& cam, hit_record& rec) const { return false; }
            */
            std::clog << "called base function" << std::endl;
            return false;
        }

};

#endif