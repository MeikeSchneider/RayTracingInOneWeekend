#include "rtweekend.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#include "vec4.h"

void test() {
    std::clog << "test\n";
    vec3 u = vec3(1, 2, 3);
    vec4 u_converted = vec3_to_vec4(u);
    vec4 v = vec4(3, 6, 9, 2);
    vec3 v_converted = vec4_to_vec3(v);
    std::clog << "u: " << u << ", u_converted: " << u_converted << std::endl;
    std::clog << "v: " << v << ", v_converted: " << v_converted << std::endl;
}

int main() {
    hittable_list world;  // make list of hittable objects

    // add sphere and "floor" to hittables
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));       // make the sphere
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));  // make green "floor" which is a sphere

    camera cam;  // create camera object

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 400;
    cam.samples_per_pixel = 100;

    test();

    cam.render(world);
}
