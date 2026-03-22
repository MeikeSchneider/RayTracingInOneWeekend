#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

bool hit_sphere(const point3& center, double radius, const ray& r) {
    // takes a sphere (defined by its center and radius) and a ray
    // checks, if they intersect by solving quadratic equation
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction()); // a = d * d
    auto b = -2.0 * dot(r.direction(), oc); // b = −2d * (C − Q)
    auto c = dot(oc, oc) - radius * radius; // c = (C − Q) * (C − Q) − r^2
    auto discriminant = b * b - 4 * a * c; // quadratic equation
    return (discriminant >= 0);
}

color ray_color(const ray& r) {
    // place sphere at (0,0,-1) with r = 0,5. If sphere intersects with way, color it red.
    if (hit_sphere(point3(0, 0, -1), 0.5, r)) 
        return color(1, 0, 0); // red

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
    auto aspect_ratio = 16.0 / 9.0; // chosen just because it's common like this
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    // if image_height < 1: set it to 1, else set to image_height
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        // instead of writing into the file like std::cout, it writes on the comand line.
        // the line numbers are being overwritten as it counts
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            // auto pixel_color = color(double(i)/(image_width-1), double(j)/(image_height-1), 0);
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}