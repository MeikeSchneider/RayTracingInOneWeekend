#ifndef MATERIAL_H
#define MATERIAL_H
#include "color.h"

class material {
    private:
    color diffuse_color;
    double diffuse_reflectivity;
    double specular_sharpness; // ns
    double specular_reflectivity; // ks

    public:
    const color& get_diffuse_color() { return diffuse_color; }  // color of the object
    const double& get_diffuse_reflectivity() { return diffuse_reflectivity; } // represents how diffuse reflective the object is
    // specular reflection sharpness parameter. Shiny surfaces ~ 100, dull surfaces ~ 1
    const double& get_specular_sharpness() { return specular_sharpness; }
    const double& get_specular_reflectivity() { return specular_reflectivity; }

    // standard constructors, no values given. All material properties get standard values
    material() {
        diffuse_color = color(1, 1, 1);
        diffuse_reflectivity = (1.0/pi);
        specular_sharpness = 10;
        specular_reflectivity = (2.0/pi);
    }

    // constructor, diffuse color is given. Everthing else is set to standard values
    material(color c) {
        diffuse_color = c;
        diffuse_reflectivity = (1.0/pi);
        specular_sharpness = 10;
        specular_reflectivity = (2.0/pi);
    }

    // constructor, diffuse color, diffuse_reflectivity are given, rest set to standard values
    material(color c, double kd) {
        diffuse_color = c;
        diffuse_reflectivity = kd;
        specular_sharpness = 10;
        specular_reflectivity = (2.0/pi);
    }

    // constructor, if diffuse_color, diffuse_reflectivity, specular_sharpness are given, rest set to standard value
    material(color c, double kd, double ns) {
        diffuse_color = c;
        diffuse_reflectivity = kd;
        specular_sharpness = ns;
        specular_reflectivity = (2.0/pi);
    }

    // constructor, if all values are given.
    material(color c, double kd, double ns, double ks) {
        diffuse_color = c;
        diffuse_reflectivity = kd;
        specular_sharpness = ns;
        specular_reflectivity = ks;
    }
};

#endif