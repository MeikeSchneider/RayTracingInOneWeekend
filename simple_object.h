#ifndef SIMPLE_OBJECT_H
#define SIMPLE_OBJECT_H

#include "matrix.h"
#include "vec3.h"

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
    
    // empty constructor: identity matrix
    simple_object() {obj_to_world_matrix = matrix(
        1, 0, 0, 0,
        0, 1, 0, 0, 
        0, 0, 1, 0,
        0, 0, 0, 1);
    }
    /*
    Identisch zu dem leeren Konstruktor drüber, aber in Schreibweise vom Tutorial
    simple_object() : obj_to_world_matrix{
        1, 0, 0, 0,
        0, 1, 0, 0, 
        0, 0, 1, 0,
        0, 0, 0, 1} {} 
    */

    // constructor, with all values given
    simple_object(vec3 translation, vec3 scale, float xRotation, float yRotation, float zRotation) {
        /*
        generates the matrices out of the values given, combines them into one matrix.
        order of operation:
        rotation: z * y * x
        everyting: scale * rotation * translation
        */
        matrix rotation = matrix::ZRotation(zRotation) * (matrix::YRotation(yRotation) * matrix::XRotation(xRotation));
        obj_to_world_matrix = matrix::Scale(scale) * (rotation *  matrix::Translation(translation));
    } 
    
    simple_object(vec3 translation, vec3 scale) {
        // constructor with translation and scale given
        obj_to_world_matrix = matrix::Scale(scale) *  matrix::Translation(translation);
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

};

#endif