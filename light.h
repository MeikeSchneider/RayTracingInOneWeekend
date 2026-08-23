#ifndef LIGHT_H
#define LIGHT_H

#include "simple_object.h"

class light : public simple_object {
    public:
    const color& get_light_color() { return light_color; }
    const double& get_intensity() { return intensity; }

    // for now, everything is a point light source. directional light source will need a direction but no position
    // standard constructor for light, light will be set at (0, 0, 0)
    light(color light_color, double intensity) : simple_object(), light_color(light_color), intensity(intensity) {}

    // constructor with a pos given
    light(vec3 pos, color light_color, double intensity) : simple_object(pos), light_color(light_color), intensity(intensity) {}

    private:
    color light_color;
    double intensity;
};

#endif