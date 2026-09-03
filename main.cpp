#include <fstream>

#include "rtweekend.h" // general main header file
#include "scene/camera.h"
#include "scene/objects_in_scene.h" // included for "what objects are in the world"
#include "scene/lights_in_scene.h" // included for "what lights are in the world"
#include "scene/hittable_obj/sphere.h"
#include "scene/hittable_obj/triangle.h" // included for individual testing
#include "io/obj_loader.h" // to load in .obj files
#include "io/image_writer.h"

int main(int argc, char* argv[]) {
    objects_in_scene world;
    lights_in_scene lights;
    image_data image;

    // command line parsing logic
    if (argc != 2){
        std::cerr << "Invalid input. Usage: ./main.exe [--ppm|--png|--statistics|--debug|--benchmark]" << std::endl;
        return 1;
    }

    // building the scene
    // lights
    light l(vec3(-10, 30, 0), color(1, 1, 1), 2.0);
    lights.add(make_shared<light>(l));

    // make a plane out of a triangle mesh to have a "floor"
    std::vector<vec3> v1 = {vec3(0, 0, 0), vec3(0, 0, -1), vec3(1, 0, 0), vec3(1, 0, -1)};
    std::vector<int> t1 = {0, 1, 2, 1, 2, 3};
    triangle_mesh plane = triangle_mesh(v1, t1, vec3(-50, -4, -1), vec3(100, 0, 55));
    world.add(make_shared<triangle_mesh>(plane));

    // add triangle mesh "fox"
    obj_loader loader;
    loader.load("obj_files/fox.obj");
    material mat = material(color(1, 0.5, 0));
    triangle_mesh m = make_triangle_mesh(loader, vec3(0, -4, -5.5), vec3(1.5, 1.5, 1.5), 0, 1.1571, 0);
    m.set_material(mat);
    world.add(make_shared<triangle_mesh>(m));

    // camera
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;  // image width to image height is 16:9 
    cam.image_width  = 400;
    cam.samples_per_pixel = 1;  // set this to 1 for testing! -> one ray per pixel
    // cam.samples_per_pixel = 100;  // anti-aliasing: 100 rays per pixel
    
    // depending on the selected mode, output different things
    std::string mode = argv[1];
    if (mode == "--ppm") {
        // render image as ppm 
        std::clog << "Rendering image as ppm" << std::endl;
        cam.render(world, lights, image);
        std::ofstream output_file("image.ppm");
        draw_ppm(output_file, image);
        output_file.close();
    } else if (mode == "--png") {
        // render image as png
        std::clog << "Rendering image as png" << std::endl;
    } else if (mode == "--statistics") {
        std::clog << "Statistics mode selected" << std::endl;
    } else if (mode == "--debug") {
        std::cout << "Debug mode selected" << std::endl;
    } else if (mode == "--benchmark") {
        std::cout << "Benchmark mode selected" << std::endl;
    } else {
        std::cerr << "Unknown option: " << mode << std::endl;
        return 1;
    }
    return 0;

    

    /* old objects
    Here are all the old things that were added to the world for testing/ different obj models
    // SPHERE
    // add sphere to the world
    // world.add(make_shared<sphere>(point3(0, 0, -1.2), 0.5)); // point, radius

    // TUTORIAL FLOOR
    // add "floor" to the world -> tutorial floor
    // world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // TRIANGLE
    // add a triangle to the world
    // world.add(make_shared<triangle>(point3(-1, -0.6, -3), point3(1, -0.6, -3), point3(0, 1.2, -3)));
    
    // TRIANGLE MESH
    // add a simple triangle mesh consisting of two triangles to the world
    std::vector<vec3> vertex_list = {point3(-1, -1, 0), point3(1, -1, 0), point3(-1, 1, 0), point3(1, 1, 0)};
    std::vector<int> triangle_list = {0, 1, 2, 1, 2, 3};
    triangle_mesh t = triangle_mesh(vertex_list, triangle_list, vec3(0, 0, -3), vec3(1, 1, 1), 0.8, 0.8, 0);
    // world.add(make_shared<triangle_mesh>(t));
    
    // TRIANGLE MESH
    // small homemade triangle mesh
    std::vector<vec3> vertex_list = {point3(-2, -0.6, -3), point3(-2, 1.8, -3), point3(-1, -0.6, -3),
                                     point3(-1, 1.2, -3), point3(1, -0.6, -3), point3(1, 1.2, -3),
                                     point3(2, -0.6, -3), point3(2, 1.8, -3)};
    // std::vector<int> triangle_list = {0, 1, 2, 1, 2, 3};
    std::vector<int> triangle_list = {0, 1, 2, 1, 2, 3, 2, 3, 4,
                                      3, 4, 5, 4, 5, 6, 5, 6, 7};
    // world.add(make_shared<triangle_mesh>(vertex_list, triangle_list));

    // OBJ CUBE, 12 triangles
    // add triangle mesh "cube" read from obj file to world
    obj_loader loader;
    loader.load("obj_files/cube.obj");
    triangle_mesh m = make_triangle_mesh(loader);
    triangle_mesh n = triangle_mesh(m.get_vertices(), m.get_triangles(), vec3(-2, 0, -5), vec3(3, 3, 3), 0.8, 0.8, 0);
    world.add(make_shared<triangle_mesh>(n));

    // CUBE BY HAND
    // content of cube.obj recreated by hand
    std::vector<vec3> list1 = {vec3(0, 0, 0), vec3(0, 1, 0), vec3(1, 1, 0), vec3(1, 0, 0), vec3(0, 0, 1), vec3(0, 1, 1), vec3(1, 1, 1), vec3(1, 0, 1)};
    std::vector<int> list2 = {2, 6, 7, 2, 7, 3, 0, 4, 5, 0, 5, 1, 6, 2, 1, 6, 1, 5, 3, 7, 4, 3, 4, 0, 7, 6, 5, 7, 5, 4, 2, 3, 0, 2, 0, 1};
    triangle_mesh o = triangle_mesh(list1, list2, vec3(-2, 0, -5), vec3(3, 3, 3), 0.8, 0.8, 0);
    world.add(make_shared<triangle_mesh>(o));

    // CAT
    // add triangle mesh "cat" read from obj file to world. 2082 triangles
    obj_loader loader;
    loader.load("obj_files/cat.obj");
    triangle_mesh m = make_triangle_mesh(loader);
    triangle_mesh n = triangle_mesh(m.get_vertices(), m.get_triangles(), vec3(10, -25, -55), vec3(0.2, 0.2, 0.2));
    world.add(make_shared<triangle_mesh>(n));
    
    // DEER
    // add triangle mesh "deer", read from obj file to world. 1508 triangles
    obj_loader loader;
    loader.load("obj_files/deer.obj");
    triangle_mesh m = make_triangle_mesh(loader);
    triangle_mesh n = triangle_mesh(m.get_vertices(), m.get_triangles(), vec3(0, -21, -35), vec3(0.03, 0.03, 0.03));
    world.add(make_shared<triangle_mesh>(n));
    
    // FOX
    // add triangle mesh "fox"
    obj_loader loader;
    loader.load("obj_files/fox.obj");
    triangle_mesh m = make_triangle_mesh(loader);
    triangle_mesh n = triangle_mesh(m.get_vertices(), m.get_triangles(), vec3(0, -4, -5), vec3(1.5, 1.5, 1.5), 0, 1.1571, 0);
    world.add(make_shared<triangle_mesh>(n));

    // BETTER SHIBA
    // add triangle mesh "shiba"
    obj_loader loader;
    loader.load("obj_files/shiba.obj");
    triangle_mesh m = make_triangle_mesh(loader);
    triangle_mesh n = triangle_mesh(m.get_vertices(), m.get_triangles(), vec3(0, -4, -16), vec3(20, 20, 20), 0, 1.57, 0);
    world.add(make_shared<triangle_mesh>(n));

    // RYUU
    obj_loader loader;
    loader.load("obj_files/shiba2.obj");
    material mat = material(color(1, 0.5, 0));
    triangle_mesh m = make_triangle_mesh(loader);
    triangle_mesh n = triangle_mesh(m.get_vertices(), m.get_triangles(), vec3(0, -4, -11), vec3(10, 10, 10), 0, 0, 0);
    n.set_material(mat);

    */

    // get debugging info: how many vertices & triangles there are 
    // std::clog << "size of vertices = " << m.get_vertices().size() << std::endl;
    // std::clog << "size of triangles = " << m.get_triangles().size() / 3 << std::endl;
    
    // get debugging info: what are the mins and max -> how to move object to fully see it.
    double min_x, min_y, min_z = 100;
    double max_x, max_y, max_z = 0;
    std::vector<vec3> vertices = m.get_vertices();
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i].x() < min_x) { min_x = vertices[i].x(); }
        if (vertices[i].y() < min_y) { min_y = vertices[i].y(); }
        if (vertices[i].z() < min_z) { min_z = vertices[i].z(); }

        if (vertices[i].x() > max_x) { max_x = vertices[i].x(); }
        if (vertices[i].y() > max_y) { max_y = vertices[i].y(); }
        if (vertices[i].z() > max_z) { max_z = vertices[i].z(); }
    } 
    // std::clog << "min_x, min_y, min_z = " << min_x << ", " << min_y << ", " << min_z << std::endl;
    // std::clog << "max_x, max_y, max_z = " << max_x << ", " << max_y << ", " << max_z << std::endl;
}
