#ifndef CAMERA_H
#define CAMERA_H

#include "simple_object.h"
#include "objects_in_scene.h"
#include "lights_in_scene.h"

class camera : public simple_object {
    public:
    double aspect_ratio = 1.0;      // Ratio of image width over height
    int    image_width  = 100;      // Rendered image width in pixel count
    int    samples_per_pixel = 10;  // Count of random samples for each pixel

    // basic constructor
    camera() : simple_object() {}

    camera(vec3 position) {
        // constructor with pos given
        // vec3 position -> vec3 translation 
        // (1, 1, 1) -> vec3 scale
        // constructor with translation and scale given
        vec3 scale = vec3(1, 1, 1);
        vec3 translation = position;
        // DONE TODO
        obj_to_world_matrix = matrix::Translation(translation) * matrix::Scale(scale);
    }

    camera(float xRotation, float yRotation, float zRotation) {
        // constructor with just rotation given
        obj_to_world_matrix = matrix::ZRotation(zRotation) * (matrix::YRotation(yRotation) * matrix::XRotation(xRotation));
    }

    camera(vec3 position, float xRotation, float yRotation, float zRotation) {
        // constructor with position and rotation given
        // DONE TODO
        matrix rotation = matrix::ZRotation(zRotation) * (matrix::YRotation(yRotation) * matrix::XRotation(xRotation));
        obj_to_world_matrix = matrix::Translation(position) * rotation;
    }

    void render(objects_in_scene& world, lights_in_scene& lights) {
        // change this function if using a different file format. 
        // TODO add the container where the color info is supposed to be saved render(world, vector& color_container)
        initialize();
        /*  P3
            400 225
            255  ...   */
        // all of this can stay the same
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        for (int j = 0; j < image_height; j++) {
            // for every remaining line of the image, print remaining line number into the terminal
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                // for multi-threading: everything starting here until write_color (including)
                // would be a job, moved into seperate function
                color pixel_color(0, 0, 0); // possible multi threading here
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    // std::clog << "ray origin, direction = " << r.origin() << ", " << r.direction() << std::endl;
                    // pixel_color += ray_color(r, world);
                    pixel_color = pixel_color + ray_color(r, world, lights);
                }
                // TODO this needs to change: write the data into color_container instead. 
                // actual image drawing is handled in main (or output.h, if that exists)
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }
        // this is fine
        // after the whole image is rendered, print "Done" into terminal
        std::clog << "\rDone.                 \n";
    }

    private:
    int    image_height;         // Rendered image height
    double pixel_samples_scale;  // Color scale factor for a sum of pixel samples
    point3 center;               // Camera center
    point3 pixel00_loc;          // Location of pixel 0, 0
    vec3   pixel_delta_u;        // Offset to pixel to the right
    vec3   pixel_delta_v;        // Offset to pixel below
    
    void initialize() {
        image_height = int(image_width / aspect_ratio);
        // image_height = (image_height < 1) ? 1 : image_height;
        if (image_height < 1) {
            image_height = 1; 
        } else {
            image_height = image_height; 
        }
        pixel_samples_scale = 1.0 / samples_per_pixel;
        // camera center at 0,0,0. 
        // y-axis goes up, x-axis goes to right, negative z-axis goes into viewing direction
        // is called "right-handed coordinates"
        center = point3(0, 0, 0);
        // Determine viewport dimensions.
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width)/image_height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);
        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;
        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    ray get_ray(int i, int j) const {
        /* Construct a camera ray originating from the origin and directed at randomly sampled
        point around the pixel location i, j. */
        // something with anti-aliasing
        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
                          + ((i + offset.x()) * pixel_delta_u)
                          + ((j + offset.y()) * pixel_delta_v);
        // set ray origin to center of camera
        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;
        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }
    
    // color ray_color(const ray& r, objects_in_scene& world) const {
    color ray_color(const ray& r, objects_in_scene& world, lights_in_scene& lights) const {
        // function takes a ray and the list of simple_objects in the world
        // this holds information about hits
        hit_record rec;

        // if stuff in the world is hit:
        // 1. world.hit writes hits into hit record, returns True
        // 2. and returns Color based on information in hit record
        if (world.hit(r, interval(0, infinity), obj_to_world_matrix, rec)) {
            // takes the normal vector from hit record, adds (1, 1, 1), multiplies by 0.5
            // (is done to scale numbers from -1, 1 to 0, 1)

            // Lambert's cosine law
            color c(0, 0, 0);
            // old way of shading: use surface normals, nothing else c = 0.5 * (rec.normal + color(1, 1, 1));
            for (const std::shared_ptr<light> l : lights.lights) {
                color l_light = l->get_intensity() * l->get_light_color();
                // rec.p = intersection point from hit_record
                // calculate vector from intersection point to ight source

                vec3 v = (vec4_to_vec3(invert(obj_to_world_matrix) * pos3_to_vec4(l->get_pos()))) - rec.p;
                double angle = dot(unit_vector(rec.normal), unit_vector(v));
                c = c + (l_light * angle);
            }
            return c;
        }
        
        // if nothing is hit: paint the background blue
        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }

};

#endif
