#ifndef HITTABLE_OBJECT_H
#define HITTABLE_OBJECT_H

#include "simple_object.h"
#include "material.h"

class hittable_object : public simple_object {
    using simple_object::simple_object;
    public:
    // getter for materials
    const material& get_material() { return mat; }
    const void set_material(material m) { mat = m; }

    hittable_object() : simple_object() {}
    hittable_object(material m) : simple_object(), mat(m) {}

    // hit function. Place holder for overwriting later, sets an object as not hittable as a standard
    virtual bool hit(const ray& r, interval ray_t, const matrix camera_to_world_matrix, hit_record& rec) const {
        std::clog << "called base function" << std::endl;
        return false;
    }

    protected: // only accessible for things that inherit
    material mat = material(color(1, 1, 1));
};

#endif