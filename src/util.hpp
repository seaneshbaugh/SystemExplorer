#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <GL/glew.h>

namespace util {
    template<typename T> T constrain(T n, T lowerLimit, T upperLimit);
    template<typename T> void swapIfLess(T &a, T &b);
    template<typename T> void swapIfGreater(T &a, T &b);
}

#endif
