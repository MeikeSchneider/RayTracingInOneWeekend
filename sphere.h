#ifndef SPHERE_H
#define SPHERE_H

#include "simple_object.h"
#include "camera_old.h"

class sphere : public simple_object {
    // für sphere is simple object die Basis Klasse
    // -> Construktoren von simple object sind basis construktoren
    // constructor
    // TODO standart construktor: sag dass wenn keine Eingabe 
    // -> benutze construktor von simple object (google how to call base constructor)
    public: 
        // calling the constructor from simple_object with no input
        sphere() : simple_object() {}

        // TODo: constructor mit float radius (vec3 scale), vec3 pos (translation) given
        // radius 1 -> scale (1, 1, 1)
        // benutze dafür basis constructor simple_object(vec3 translation, vec3 scale)
        
        
        sphere(vec3 position, float radius) {
            // vec3 position -> vec3 translation 
            // float radius -> vec3 scale
            // constructor with translation and scale given
            vec3 scale = vec3(radius, radius, radius);
            vec3 translation = position;
            obj_to_world_matrix = matrix::Scale(scale) *  matrix::Translation(translation);
        }
    
        bool hit(const ray& r, interval ray_t, camera_old& cam, hit_record& rec) const {
        // von Sören erklärtes Mathe hier einfügen 
        return false;
        }
};

#endif