#ifndef OBJECTS_IN_SCENE_H
#define OBJECTS_IN_SCENE_H

#include "simple_object.h"
#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;  // does memory management automatically so we don't need to worry about it


class objects_in_scene {
  public:
    // basically a list containing shared pointers pointing to different hittables
    std::vector<shared_ptr<simple_object>> objects;
    objects_in_scene() {}
    objects_in_scene(shared_ptr<simple_object> object) { add(object); }
    void clear() { objects.clear(); }

    void add(shared_ptr<simple_object> object) {
        objects.push_back(object);
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;
        // iterate through list of objects with interation object "object"
        for (const auto& object : objects) {
            // "->"" is dereferencing
            if (object->hit(r, interval(ray_t.min, closest_so_far), matrix(), temp_rec)) {
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