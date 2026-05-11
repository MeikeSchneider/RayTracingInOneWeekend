#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"


int main() {
    hittable_list world;  // make list of hittable objects

    // add sphere and "floor" to hittables
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));       // make the sphere
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));  // make green "floor" which is a sphere

    camera cam;  // create camera object

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 400;
    cam.samples_per_pixel = 100;

    cam.render(world);
}