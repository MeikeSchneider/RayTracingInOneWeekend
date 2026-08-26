#ifndef OBJECTS_IN_SCENE_H
#define OBJECTS_IN_SCENE_H

# include "hittable_obj/hittable_object.h"

using std::make_shared;
using std::shared_ptr;  // does memory management automatically so we don't need to worry about it


class objects_in_scene {
  public:
    // basically a list containing shared pointers pointing to different hittables
    std::vector<shared_ptr<hittable_object>> objects;
    objects_in_scene() {}
    objects_in_scene(shared_ptr<hittable_object> object) { add(object); }
    void clear() { objects.clear(); }

    void add(shared_ptr<hittable_object> object) {
        objects.push_back(object);
    }

    bool hit(const ray& r, interval ray_t, matrix cam_to_world_matrix, hit_record& rec) const {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;
        // iterate through list of objects with interation object "object"
        for (const auto& object : objects) {
            // "->"" is dereferencing, needed because of smart pointer
            if (object->hit(r, interval(ray_t.min, closest_so_far), cam_to_world_matrix, temp_rec)) {
                // wenn if statement true zurück liefert wurde etwas getroffen und der hit aufruf hat etw in temp_rec geschrieben.
                // std::clog << "hit detected" << std::endl;
                if (temp_rec.t < closest_so_far) {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }
        }

        return hit_anything;
    }
};

#endif