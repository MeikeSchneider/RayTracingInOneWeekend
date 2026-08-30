#ifndef IMAGE_WRITER_H
#define IMAGE_WRITER_H

#include "../rendering/color.h"

void draw_ppm(std::ostream& out, image_data& container) {
    int image_width = container.width;
    int image_height = container.height;
    /*  P3
        400 225
        255  ...   */
    out << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    static const interval intensity(0.000, 0.999);
    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            int index = j * image_width + i;
            color c = container.color_container[index];
            // Translate the [0,1] component values to the byte range [0,255]
            int rbyte = int(256 * intensity.clamp(c.r));
            int gbyte = int(256 * intensity.clamp(c.g));
            int bbyte = int(256 * intensity.clamp(c.b));

            // Write out the pixel color components.
            out << int(rbyte) << ' ' << gbyte << ' ' << bbyte << '\n';
        }
    }
}


# endif