#ifndef INTERVAL_H
#define INTERVAL_H
/*
number range tool.
In the ray tracer, it is mainly used to define which t values along a ray count as valid hits.
Provided functionality:
    - define intervals in which we want to check or accept results
    - check if a value is inside an interval, including or excluding boundaries
    - clamp numbers to certain ranges
*/ 
#include <cmath>
const double infinity = std::numeric_limits<double>::infinity();

class interval {
  public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {} // Default interval is empty

    interval(double min, double max) : min(min), max(max) {}

    double size() const {
        return max - min;
    }

    // check if a number x is within the interval (min, max), including min and max
    bool contains(double x) const {
        return min <= x && x <= max;
    }

    // check if a number is within the interval (min, max), excluding min and max
    bool surrounds(double x) const {
        return min < x && x < max;
    }

    // helper function to clamp value to interval [0,1]
    double clamp(double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    static const interval empty, universe;
};

inline const interval interval::empty    = interval(+infinity, -infinity);
inline const interval interval::universe = interval(-infinity, +infinity);

#endif