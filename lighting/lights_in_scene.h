#ifndef LIGHTS_IN_SCENE_H
#define LIGHTS_IN_SCENE_H

#include "light.h"

using std::make_shared;
using std::shared_ptr;  // does memory management automatically so we don't need to worry about it

class lights_in_scene {
    public:
    // a list containing shared pointers, pointing to different lights
    std::vector<shared_ptr<light>> lights;
    lights_in_scene() {}
    lights_in_scene(shared_ptr<light> l) { add(l); }

    void clear() { lights.clear(); }

    void add(shared_ptr<light> l) {
        lights.push_back(l);
    }
};

#endif