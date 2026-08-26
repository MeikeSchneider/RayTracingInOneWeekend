#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "ray.h"
#include "lighting/material.h"

class hit_record {
  public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
    material mat;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.
        front_face = dot(r.direction(), outward_normal) < 0;
        // normal = front_face ? outward_normal : -outward_normal;
        if (front_face) {
          normal = outward_normal;
        } else {
          normal = -outward_normal;
        }
    }
};

#endif