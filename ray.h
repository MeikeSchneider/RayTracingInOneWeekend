#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
  // P(t) = A + t * b
  public:
    // empty constructor: empty ray
    ray() {}
    
    // give origin and direction value, use those to set orig and dir, give object
    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}
    
    // refernece to origin: ray origin A, return private var oig
    const point3& origin() const  { return orig; }
    // dir: ray direction b
    const vec3& direction() const { return dir; }

    // P(t) = A + t * b
    point3 at(double t) const {
        return orig + t * dir;
    }

  private:
    point3 orig;
    vec3 dir;
};

#endif