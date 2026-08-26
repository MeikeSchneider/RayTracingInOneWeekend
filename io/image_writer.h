#ifndef IMAGE_WRITER_H
#define IMAGE_WRITER_H

#include "../rendering/color.h"

// have different functions that convert the raw data
// that is saved in color_container into the desired file format. Do not export image though!

// TODO: change return type to expected type from file format
void write_color(std::ostream& out, const color& pixel_color) {
    /*
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();
    */
    auto r = pixel_color.r;
    auto g = pixel_color.g;
    auto b = pixel_color.b;

    // Translate the [0,1] component values to the byte range [0,255].
    
    // updated color function to sample multiple times per pixel
    // using clamping function to stay in [0, 1] range
    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

# endif