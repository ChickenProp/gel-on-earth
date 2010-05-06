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

template <typename T>
sf::Vector3<T> vProjectXY (const sf::Vector3<T> &a) {
	return sf::Vector3<T>(a.x, a.y, 0);
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
sf::Vector3<T> vNormalize (const sf::Vector3<T> &a) {
	if (a.x == 0 && a.y == 0 && a.z == 0)
		return a;
	else
		return a / ((T) vLength(a));
}

template <typename T>
double vAngleBetween_r(const sf::Vector3<T> &a, const sf::Vector3<T> &b) {
	double la = vLength(a);
	double lb = vLength(b);

	if (la == 0 || lb == 0)
		return 0;

	/* Sometimes rounding errors will produce a value slightly outside
	   [-1, 1], so we need to clamp. */
	return acos(clampd(vDot(a, b)/(la*lb), -1, 1));
}

template <typename T>
double vAngleBetween(const sf::Vector3<T> &a, const sf::Vector3<T> &b) {
	return rad2deg(vAngleBetween_r(a,b));
}

template <typename T>
double vTheta_r(const sf::Vector3<T> &a) {
	return atan2(a.z, vLength(vProjectXY(a)));
}

template <typename T>
double vTheta(const sf::Vector3<T> &a) {
	return rad2deg(vTheta_r(a));
}

template <typename T>
double vPhi_r(const sf::Vector3<T> &a) {
	return atan2(a.y, a.x);
}
template <typename T>
double vPhi(const sf::Vector3<T> &a) {
	return rad2deg(vPhi_r(a));
}

inline sf::Vector3f vSpherical_r(double r, double theta, double phi) {
	return sf::Vector3f(r*cos(phi)*cos(theta),
	                    r*sin(phi)*cos(theta),
	                    r*sin(theta));
}

inline sf::Vector3f vSpherical(double r, double theta, double phi) {
	return vSpherical_r(r, deg2rad(theta), deg2rad(phi));
}

#endif
