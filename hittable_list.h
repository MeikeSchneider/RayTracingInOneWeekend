#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "interval.h"

#include <memory>
#include <vector>

/*
shared_ptr<type>: is a pointer to some type with reference-counting. 
Every time it's value is assigned to another shared pointer, reference count is increased
As shared pointers go to the end of a block or a function, the reference count is decreased
If count is zero -> object safely deleted

make_shared<thing>(thing_constructor_params ...) allocates a new instance of type thing, 
using the constructor parameters. It returns a shared_ptr<thing>. 
std::shared_ptr is included with the <memory> header.

using statement: tells the compiler that we'll be getting shared_ptr and make_shared 
from the std library, so we don't need to prefix these with std:: every time we reference them. 
*/
using std::make_shared;
using std::shared_ptr;  // does memory management automatically so we don't need to worry about it

class hittable_list : public hittable {
  public:
    // basically a list containing shared pointers pointing to different hittables
    std::vector<shared_ptr<hittable>> objects;
    /*
    zB erzeuge Kugel. Möchte mehrere Sachen damit machen, also zeigen mehrere pointer drauf
    shared pointer hat counter um sich zu merken, wie viele pointer drauf zeigen.
    Wenn nichts mehr drauf zeigt weiß der shared pointer, dass das Objekt gelöscht werden soll.
    */

    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<hittable> object) {
        objects.push_back(object);
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;
        
        for (const auto& object : objects) {
            if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                // -> is dereferencing
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};

#endif