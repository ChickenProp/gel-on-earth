#ifndef _UTIL_H
#define _UTIL_H

#include "includes.h"
#include "math.h"

/* The templated functions need to be defined here because of C++ weirdness
 * (which actually makes sense). The other functions could be put into a .cpp
 * file. But since I don't, they need to be inline to avoid multiple definition
 * errors. */

inline double clampd (double x, double min, double max) {
	return x <= min ? min : (x >= max ? max : x);
}

inline double deg2rad (double d) {
	return d * M_PI / 180.0;
}

inline double rad2deg (double r) {
	return r * 180.0 / M_PI;
}

#endif
