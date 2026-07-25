#ifndef CAMERA_H
#define CAMERA_H

#include "simple_object.h"

class camera : public simple_object {
    public:
    // basic constructor
    camera() : simple_object() {}

    // constructor with pos given
    camera(vec3 position) {
        // vec3 position -> vec3 translation 
        // (1, 1, 1) -> vec3 scale
        // constructor with translation and scale given
        vec3 scale = vec3(1, 1, 1);
        vec3 translation = position;
        obj_to_world_matrix = matrix::Scale(scale) *  matrix::Translation(translation);
    }

    // constructor with just rotation given
    camera(float xRotation, float yRotation, float zRotation) {
        obj_to_world_matrix = matrix::ZRotation(zRotation) * (matrix::YRotation(yRotation) * matrix::XRotation(xRotation));
    }

    // constructor with position and rotation given
    camera(vec3 position, float xRotation, float yRotation, float zRotation) {
        matrix rotation = matrix::ZRotation(zRotation) * (matrix::YRotation(yRotation) * matrix::XRotation(xRotation));
        obj_to_world_matrix = rotation *  matrix::Translation(position);
    }

};

#endif
