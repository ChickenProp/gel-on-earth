#ifndef PH_MATH_UTIL_H
#define PH_MATH_UTIL_H

#include "math.h"

namespace ph {

inline float clampf (float x, float min, float max) {
	return x <= min ? min : (x >= max ? max : x);
}

inline float deg2rad (float d) {
	return d * M_PI / 180.0;
}

inline float rad2deg (float r) {
	return r * 180.0 / M_PI;
}

}

#endif
