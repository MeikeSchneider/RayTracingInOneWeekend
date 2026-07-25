#ifndef SPHERE_H
#define SPHERE_H

#include "simple_object.h"
#include "camera.h"

class sphere : simple_object {
    // für sphere is simple object die Basis Klasse
    // -> Construktoren von simple object sind basis construktoren
    // constructor
    // TODO standart construktor: sag dass wenn keine Eingabe 
    // -> benutze construktor von simple object (google how to call base constructor)
    // TODo: constructor mit float radius (vec3 scale), vec3 pos (translation) given
    // radius 1 -> scale (1, 1, 1)
    // benutze dafür basis constructor simple_object(vec3 translation, vec3 scale)
    
    bool hit(const ray& r, interval ray_t, camera& cam, hit_record& rec) const {
    // von Sören erklärtes Mathe hier einfügen 
    return false;
    }
};

#endif