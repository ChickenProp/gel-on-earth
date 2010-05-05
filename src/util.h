#ifndef _UTIL_H
#define _UTIL_H

#include "includes.h"

double clampd (double x, double min, double max);

double deg2rad (double d);
double rad2deg (double r);

template <typename T>
sf::Vector3<T> vProjectXY (const sf::Vector3<T> &a);

template <typename T>
sf::Vector3<T> vCross (const sf::Vector3<T> &a, const sf::Vector3<T> &b);

template <typename T>
T vDot (const sf::Vector3<T> &a, const sf::Vector3<T> &b);

template <typename T>
T vLengthSquared (const sf::Vector3<T> &a);

template <typename T>
double vLength (const sf::Vector3<T> &a);

template <typename T>
sf::Vector3<T> vNormalize(const sf::Vector3<T> &a);

template <typename T>
double vAngleBetween_r(const sf::Vector3<T> &a, const sf::Vector3<T> &b);

template <typename T>
double vAngleBetween(const sf::Vector3<T> &a, const sf::Vector3<T> &b);

double vTheta_r(const sf::Vector3f &a);
double vTheta(const sf::Vector3f &a);
double vPhi_r(const sf::Vector3f &a);
double vPhi(const sf::Vector3f &a);

sf::Vector3f vSpherical_r(double r, double theta, double phi);
sf::Vector3f vSpherical(double r, double theta, double phi);

#endif
