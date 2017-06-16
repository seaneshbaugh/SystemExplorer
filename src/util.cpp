#include "util.hpp"

template<typename T> T util::constrain(T n, T lowerLimit, T upperLimit) {
    if (lowerLimit == upperLimit) {
        return lowerLimit;
    }

    swapIfLess(upperLimit, lowerLimit);

    if (n < lowerLimit) {
        return lowerLimit;
    } else {
        if (n > upperLimit) {
            return upperLimit;
        } else {
            return n;
        }
    }
}

template<typename T> void util::swapIfLess(T &a, T &b) {
    if (a < b) {
        T c = a;

        a = b;

        b = c;
    }
}

template<typename T> void util::swapIfGreater(T &a, T &b) {
    swapIfLess(b, a);
}
