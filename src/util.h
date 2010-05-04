#ifndef _UTIL_H
#define _UTIL_H

#include "includes.h"
#include "math.h"

double deg2rad (double d) {
	return d * M_PI / 180.0;
}

double rad2deg (double r) {
	return r * 180.0 / M_PI;
}

template <typename T>
sf::Vector3<T> vCross (const sf::Vector3<T> &a, const sf::Vector3<T> &b) {
	return sf::Vector3<T>(a.y*b.z - a.z*b.y,
	                      a.z*b.x - a.x*b.z,
	                      a.x*b.y - a.y*b.x);
}

template <typename T>
T vDot (const sf::Vector3<T> &a, const sf::Vector3<T> &b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

template <typename T>
T vLengthSquared (const sf::Vector3<T> &a) {
	return vDot(a,a);
}

template <typename T>
double vLength (const sf::Vector3<T> &a) {
	return sqrt(vLengthSquared(a));
}

template <typename T>
double vAngleBetween_r(const sf::Vector3<T> &a, const sf::Vector3<T> &b) {
	double la = vLength(a);
	double lb = vLength(b);

	if (la == 0 || lb == 0)
		return 0;

	return acos(vDot(a, b)/(la*lb));
}

template <typename T>
double vAngleBetween(const sf::Vector3<T> &a, const sf::Vector3<T> &b) {
	return rad2deg(vAngleBetween_r(a,b));
}

#endif
