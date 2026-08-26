#include "rtweekend.h" // general main header file
#include "camera.h"
#include "simple_object.h" // included for testing
#include "objects_in_scene.h" // included for "what objects are in the world"
#include "lighting/lights_in_scene.h"
#include "geometry/sphere.h" // included for "floor"
#include "geometry/triangle.h" // included for testing
#include "geometry/triangle_mesh.h" // needed for meshes
#include "obj_loader.h" // to load in .obj files

void test_simple_obj() {
    // test the empty constructor
    simple_object obj_1 = simple_object();
    std::clog << "object_1 = " << obj_1.obj_to_world_matrix << std::endl;
    // test constructor with scale and translation given
    simple_object obj_2 = simple_object(vec3(1, 2, 3), vec3(2, 2, 2), 0, 0, 0);
    std::clog << "object_2 = " << obj_2.obj_to_world_matrix << std::endl;
    // test the move function
    obj_1.move(vec3(3, 4, 5));
    std::clog << "object_1 = " << obj_1.obj_to_world_matrix << std::endl;
    obj_2.move(vec3(-1, -2, -3));
    std::clog << "object_2 = " << obj_2.obj_to_world_matrix << std::endl;
    // test the place function
    obj_1.place(vec3(3, 4, 5));
    std::clog << "object_1 = " << obj_1.obj_to_world_matrix << std::endl;
    obj_2.place(vec3(-1, -2, -3));
    std::clog << "object_2 = " << obj_2.obj_to_world_matrix << std::endl;
}

void test_sphere() {
    // test constructors
    sphere s = sphere();
    // std::clog << "s = " << s.obj_to_world_matrix << std::endl;
    sphere t = sphere(vec3(1, 2, 3), 5);
    // std::clog << "t = " << t.obj_to_world_matrix << std::endl;
    ray r = ray(vec3(0, 0, 0), vec3(1, 1, 1));
    hit_record rect;
    bool result = s.hit(r, interval(0, infinity), matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1), rect);
    std::clog << "result = " << result << std::endl;
}

void test_camera() {
    // test basic constructor
    camera b = camera();
    std::clog << "b = " << b.obj_to_world_matrix << std::endl;
    // test constructor with pos given
    camera c = camera(vec3(1, 2, 3));
    std::clog << "c = " << c.obj_to_world_matrix << std::endl;
    // test constructor with just rotation given
    camera d = camera(90, 0, 0);
    std::clog << "d = " << d.obj_to_world_matrix << std::endl;
    // test constructor with pos and rotation given
    camera e = camera(vec3(1, 2, 3), 90, 0, 0);
    std::clog << "e = " << e.obj_to_world_matrix << std::endl;
}

void test_triangle() {
    // test basic constructor
    triangle t = triangle(vec3(1, 1, 1), vec3(2, 2, 2), vec3(3, 3, 3));
    std::clog << "triangle positions = " << t.get_a() << ", " << t.get_b() << ", " << t.get_c() << ", " << std::endl;
    std::clog << "triangle matrix = " << t.obj_to_world_matrix << std::endl;
    // test constructor with pos
    triangle s = triangle(vec3(0, 0, 0), vec3(-2, -2, -2), vec3(3, 3, 3), vec3(1, 2, 3));
    std::clog << "triangle positions = " << s.get_a() << ", " << s.get_b() << ", " << s.get_c() << ", " << std::endl;
    std::clog << "triangle matrix = " << s.obj_to_world_matrix << std::endl;
    // test constructor with pos, scale
    triangle u = triangle(vec3(0.0, 0.5, 0), vec3(-2, -2, -2), vec3(3.2, 3.0, 3.1), vec3(1, 2, 3), vec3(2, 2, 2));
    std::clog << "triangle positions = " << u.get_a() << ", " << u.get_b() << ", " << u.get_c() << ", " << std::endl;
    std::clog << "triangle matrix = " << u.obj_to_world_matrix << std::endl;
    // test constructor with pos, scale, rotations
    triangle v = triangle(vec3(0.0, 0.5, 0), vec3(-2, -2, -2), vec3(3.2, 3.0, 3.1), vec3(1, 2, 3), vec3(2, 2, 2), 90.0, 180.0, 90.0);
    std::clog << "triangle positions = " << v.get_a() << ", " << v.get_b() << ", " << v.get_c() << ", " << std::endl;
    std::clog << "triangle matrix = " << v.obj_to_world_matrix << std::endl;
}

void test_triangle_hit() {
    // test the hit function for the triangle
    
    // triangle gets hit by ray, t = 5, intersection point = (1, 1, 5)
    triangle t = triangle(vec3(0, 0, 4), vec3(3, 0, 4), vec3(0, 3, 7));
    ray r = ray(vec3(1, 1, 0), vec3(0, 0, 1));
    matrix id = matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    hit_record rect;
    vec3 plane_normal = cross(t.get_b() - t.get_a(), t.get_c() - t.get_a());
    std::clog << "hit example: plane normal = " << plane_normal << std::endl;
    std::clog << "hit example: dot product plane normal, (a - ray direction) = " << dot(plane_normal, (t.get_a() - r.direction())) << std::endl;
    std::clog << "hit example: the ray hit the plane? " << t.hit(r, interval(0, infinity), id, rect) << std::endl;
    
    // triangle is paralell to ray, no t, no intersection point
    triangle s = triangle(vec3(0, 0, 4), vec3(0, 3, 4), vec3(0, 0, 7));
    ray v = ray(vec3(1, 1, 0), vec3(0, 1, 0));
    vec3 plane_normal_2 = cross(s.get_b() - s.get_a(), s.get_c() - s.get_a());
    std::clog << "paralell example: plane normal = " << plane_normal_2 << std::endl;
    std::clog << "paralell example: dot product plane normal, (a - ray direction) = " << dot(plane_normal_2, (s.get_a() - v.direction())) << std::endl;
    std::clog << "paralell example: did the ray hit the plane? " << s.hit(v, interval(0, infinity), id, rect) << std::endl;
    
    // triangle does not get hit by ray. Ray hits the plane but not the triangle, t = 5, intersection point = (4, 1, 5)
    triangle q = triangle(vec3(0, 0, 4), vec3(3, 0, 4), vec3(0, 3, 7));
    ray u = ray(vec3(4, 1, 0), vec3(0, 0, 1));
    vec3 plane_normal_3 = cross(q.get_b() - q.get_a(), q.get_c() - q.get_a());
    std::clog << "plane hit example: plane normal = " << plane_normal_3 << std::endl;
    std::clog << "plane hit example: dot product plane normal, (a - ray direction) = " << dot(plane_normal_3, (q.get_a() - u.direction())) << std::endl;
    std::clog << "plane hit example: did the ray hit the plane? " << q.hit(u, interval(0, infinity), id, rect) << std::endl;
    
    // triangle gets hit by ray. Ray hits the edge of the triangle, t = 5, intersection point = (1, 1, 5)
    triangle p = triangle(vec3(0, 0, 5), vec3(2, 0, 5), vec3(0, 2, 5));
    ray w = ray(vec3(1, 1, 0), vec3(0, 0, 1));
    vec3 plane_normal_4 = cross(p.get_b() - p.get_a(), p.get_c() - p.get_a());
    std::clog << "edge hit example: plane normal = " << plane_normal_4 << std::endl;
    std::clog << "edge hit example: dot product plane normal, (a - ray direction) = " << dot(plane_normal_4, (p.get_a() - w.direction())) << std::endl;
    std::clog << "edge hit example: did the ray hit the plane? " << p.hit(w, interval(0, infinity), id, rect) << std::endl;
}

void test_triangle_mesh() {
    // first constructor
    std::vector<vec3> vertex_list = {vec3(0, 0, 5), vec3(2, 0, 5), vec3(0, 2, 5)};
    std::vector<int> triangle_list = {0, 1, 2};
    triangle_mesh m = triangle_mesh(vertex_list, triangle_list);
    std::clog << "vertex_list = " << vertex_list << std::endl;
    std::clog << "triangle_list = " << triangle_list << std::endl;
    std::clog << "obj_to_world_matrix1 = " << m.obj_to_world_matrix << std::endl;
    
    // test getters
    std::clog << "vertices: " << m.get_vertices() << std::endl;
    std::clog << "triangles: " << m.get_triangles() << std::endl;

    // second constructor
    triangle_mesh n = triangle_mesh(vertex_list, triangle_list, vec3(1, 2, 3));
    std::clog << "obj_to_world_matrix2 = " << n.obj_to_world_matrix << std::endl;

    // third constructor
    triangle_mesh o = triangle_mesh(vertex_list, triangle_list, vec3(1, 2, 3), vec3(4, 5, 6));
    std::clog << "obj_to_world_matrix3 = " << o.obj_to_world_matrix << std::endl;

    // fourth constructor
    triangle_mesh p = triangle_mesh(vertex_list, triangle_list, vec3(1, 2, 3), vec3(4, 5, 6), 90.0, 180.0, 90.0);
    std::clog << "obj_to_world_matrix4 = " << p.obj_to_world_matrix << std::endl;
}

void test_mesh_hit() {
    // triangle gets hit by ray, t = 5, intersection point = (1, 1, 5)
    std::vector<vec3> vertex_list = {vec3(0, 0, 4), vec3(3, 0, 4), vec3(0, 3, 7)};
    std::vector<int> triangle_list = {0, 1, 2};
    triangle_mesh t = triangle_mesh(vertex_list, triangle_list);
    ray r = ray(vec3(1, 1, 0), vec3(0, 0, 1));
    matrix id = matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    hit_record rect;
    std::clog << "hit example: the ray hit the plane? " << t.hit(r, interval(0, infinity), id, rect) << std::endl;

    // triangle is paralell to ray, no t, no intersection point
    vertex_list = {vec3(0, 0, 4), vec3(0, 3, 4), vec3(0, 0, 7)};
    t = triangle_mesh(vertex_list, triangle_list);
    ray v = ray(vec3(1, 1, 0), vec3(0, 1, 0));
    std::clog << "paralell example: did the ray hit the plane? " << t.hit(v, interval(0, infinity), id, rect) << std::endl;
    
    // triangle does not get hit by ray. Ray hits the plane but not the triangle, t = 5, intersection point = (4, 1, 5)
    vertex_list = {vec3(0, 0, 4), vec3(3, 0, 4), vec3(0, 3, 7)};
    t = triangle_mesh(vertex_list, triangle_list);
    ray u = ray(vec3(4, 1, 0), vec3(0, 0, 1));
    std::clog << "plane hit example: did the ray hit the plane? " << t.hit(u, interval(0, infinity), id, rect) << std::endl;
    
    // triangle gets hit by ray. Ray hits the edge of the triangle, t = 5, intersection point = (1, 1, 5)
    vertex_list = {vec3(0, 0, 5), vec3(2, 0, 5), vec3(0, 2, 5)};
    t = triangle_mesh(vertex_list, triangle_list);
    ray w = ray(vec3(1, 1, 0), vec3(0, 0, 1));
    std::clog << "edge hit example: did the ray hit the plane? " << t.hit(w, interval(0, infinity), id, rect) << std::endl;

    // more triangles get hit by ray. Intersections: (2/3, 2/3, 2/3), 
    vertex_list = {vec3(2, 0, 0), vec3(0, 2, 0), vec3(0, 0, 2), // intersection: (2/3, 2/3, 2/3) 0,66666
                   vec3(5, 1, 1), vec3(1, 5, 1), vec3(1, 1, 5), // intersection: (7/3, 7/3, 7/3) 2,33333
                   vec3(8, 2, 2), vec3(2, 8, 2), vec3(2, 2, 8)};// intersection: (4, 4, 4)
    triangle_list = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    t = triangle_mesh(vertex_list, triangle_list);
    ray x = ray(vec3(0, 0, 0), vec3(1, 1, 1));
    std::clog << "edge hit example: did the ray hit the plane? " << t.hit(x, interval(0, infinity), id, rect) << std::endl;
}

void test_obj_loader() {
    obj_loader loader;
    loader.load("obj_files/cube.obj");
    std::clog << "vertices_lst = " << loader.get_vertices_lst() << std::endl;
    std::clog << "normals_lst = " << loader.get_normals_lst() << std::endl;
    std::clog << "texCoods_lst = " << loader.get_texCoords_lst() << std::endl;
    std::clog << "faces_lst = " << loader.get_faces_lst() << std::endl;
    triangle_mesh m = make_triangle_mesh(loader);
    std::clog << "m.vertices = " << m.get_vertices() << std::endl;
    std::clog << "m.triangles = " << m.get_triangles() << std::endl;
}

int main() {
    // TODO comand line parsing logic (if (--ppm etc))
    objects_in_scene world;
    lights_in_scene lights;

    light l(vec3(-10, 30, 0), color(1, 1, 1), 2.0);
    lights.add(make_shared<light>(l));

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

    */

    // make a plane out of a triangle mesh to have a "floor"
    std::vector<vec3> v1 = {vec3(0, 0, 0), vec3(0, 0, -1), vec3(1, 0, 0), vec3(1, 0, -1)};
    std::vector<int> t1 = {0, 1, 2, 1, 2, 3};
    // triangle_mesh plane = triangle_mesh(v1, t1, vec3(-50, -22, -1), vec3(100, 0, 55));
    triangle_mesh plane = triangle_mesh(v1, t1, vec3(-50, -4, -1), vec3(100, 0, 55));
    world.add(make_shared<triangle_mesh>(plane));
    
    // add triangle mesh "fox"
    obj_loader loader;
    loader.load("obj_files/fox.obj");
    material mat = material(color(1, 0.5, 0));
    triangle_mesh m = make_triangle_mesh(loader);
    triangle_mesh n = triangle_mesh(m.get_vertices(), m.get_triangles(), vec3(0, -4, -5.5), vec3(1.5, 1.5, 1.5), 0, 1.1571, 0);
    n.set_material(mat);

    // add ryuu
    /*
    obj_loader loader;
    loader.load("obj_files/shiba2.obj");
    material mat = material(color(1, 0.5, 0));
    triangle_mesh m = make_triangle_mesh(loader);
    triangle_mesh n = triangle_mesh(m.get_vertices(), m.get_triangles(), vec3(0, -4, -11), vec3(10, 10, 10), 0, 0, 0);
    n.set_material(mat); */

    
    // get debugging info: how many vertices & triangles there are 
    // std::clog << "size of vertices = " << n.get_vertices().size() << std::endl;
    // std::clog << "size of triangles = " << n.get_triangles().size() / 3 << std::endl;
    
    // get debugging info: what are the mins and max -> how to move object to fully see it.
    double min_x, min_y, min_z = 100;
    double max_x, max_y, max_z = 0;
    std::vector<vec3> vertices = n.get_vertices();
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
    
    // add object to world
    world.add(make_shared<triangle_mesh>(n));
    
    camera cam; // create camera object

    cam.aspect_ratio = 16.0 / 9.0;  // image width to image height is 16:9 
    cam.image_width  = 400;
    cam.samples_per_pixel = 1;  // // set this to 1 for testing!
    // cam.samples_per_pixel = 100;  // normal value, send 100 rays per pixel into scene, used for anti-aliasing

    // call test functions here
    // test_triangle();
    // test_triangle_mesh();
    // test_mesh_hit();
    // test_obj_loader();

    cam.render(world, lights);
}
