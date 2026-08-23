#ifndef MATERIAL_H
#define MATERIAL_H
#include "color.h"

class material {
    private:
    color diffuse_color;

    public:
    const color& get_diffuse_color() { return diffuse_color; }

    material() { diffuse_color = color(1, 1, 1); }
    material(color c) { diffuse_color = c; }
};

#endif