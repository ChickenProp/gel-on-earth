#ifndef PH_VECTOR_H
#define PH_VECTOR_H

#include "math.h"

namespace ph {

class vec2f {
public:
	float x;
	float y;

	vec2f() : x(0.f), y(0.f) {}
	vec2f(const float _x, const float _y) : x(_x), y(_y) {}

	float lengthSquared () const {
		return x*x + y*y;
	}
	float length () const {
		return sqrt(x*x + y*y);
	}

	float distanceSquared (const vec2f &v) const {
		return (*this - v).lengthSquared();
	}
	float distance (const vec2f &v) const {
		return (*this - v).length();
	}

	vec2f normalize () const {
		if (lengthSquared() == 0)
			return *this;
		else
			return *this / length();
	}

	float dot (const vec2f &v) const {
		return x*v.x + y*v.y;
	}
	float cross (const vec2f &v) const {
		return x*v.y - y*v.x;
	}

	vec2f project(const vec2f &v) const {
		return v.normalize() * (this->dot(v.normalize()));
	}
	vec2f project(const vec2f &u, const vec2f &v) const {
		return u + (*this - u).project(v - u);
	}

	vec2f operator+ (const vec2f &v) const {
		return vec2f(x + v.x, y + v.y);
	}
	vec2f operator- (const vec2f &v) const {
		return vec2f(x - v.x, y - v.y);
	}
	vec2f operator- () const {
		return vec2f(-x, -y);
	}
	vec2f operator* (const float a) const {
		return vec2f(a*x, a*y);
	}
	vec2f operator/ (const float a) const {
		return vec2f(x/a, y/a);
	}

	vec2f& operator+= (const vec2f v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	vec2f& operator-= (const vec2f v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	vec2f& operator*= (const float a) {
		x *= a;
		y *= a;
		return *this;
	}
	vec2f& operator/= (const float a) {
		x /= a;
		y /= a;
		return *this;
	}

#ifdef SFML_VECTOR2_HPP
	template <typename T>
	vec2f(const sf::Vector2<T> &v) : x(v.x), y(v.y) {}

	template <typename T>
	operator sf::Vector2<T>() {
		return sf::Vector2<T>((T)x, (T)y);
	}
#endif

};

inline vec2f operator* (const float a, const vec2f &v) {
	return vec2f(a*v.x, a*v.y);
}

class vec3f {
public:
	float x;
	float y;
	float z;

	vec3f () : x(0.f), y(0.f), z(0.f) {}
	vec3f (float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	static vec3f spherical(float r, float phi, float theta) {
		float p = phi * M_PI / 180.f;
		float t = theta * M_PI / 180.f;
		return vec3f(r*cos(p)*cos(t),
		             r*sin(p)*cos(t),
		             r*sin(t));
	}

	vec3f cross(const vec3f &v) const {
		return vec3f(y * v.z - z * v.y,
		             z * v.x - x * v.z,
		             x * v.y - y * v.x);
	}

	float lengthSquared() const {
		return x*x + y*y + z*z;
	}
	float length() const {
		return sqrt(lengthSquared());
	}

	vec3f normalize() const {
		float len = length();
		if (len == 0)
			return *this;
		else
			return *this/len;
	}

	vec3f projectXY() const {
		return vec3f(x, y, 0);
	}

	float phi() const {
		return atan2(y, x) * 180.f / M_PI;
	}

	float theta() const {
		return atan2(z, projectXY().length()) * 180.f / M_PI;
	}

	vec3f operator+ (const vec3f &v) const {
		return vec3f(x + v.x, y + v.y, z + v.z);
	}
	vec3f operator- (const vec3f &v) const {
		return vec3f(x - v.x, y - v.y, z - v.z);
	}
	vec3f operator- () const {
		return vec3f(-x, -y, -z);
	}
	vec3f operator* (const float a) const {
		return vec3f(a*x, a*y, a*z);
	}
	vec3f operator/ (const float a) const {
		return vec3f(x/a, y/a, z/a);
	}

	vec3f& operator+= (const vec3f v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	vec3f& operator-= (const vec3f v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	vec3f& operator*= (const float a) {
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}
	vec3f& operator/= (const float a) {
		x /= a;
		y /= a;
		z /= a;
		return *this;
	}


#ifdef SFML_VECTOR3_HPP
	template <typename T>
	vec3f(const sf::Vector3<T> &v) : x(v.x), y(v.y), z(v.z) {}

	template <typename T>
	operator sf::Vector3<T>() {
		return sf::Vector3<T>((T)x, (T)y, (T)z);
	}
#endif

};

inline vec3f operator* (const float a, const vec3f &v) {
	return vec3f(a*v.x, a*v.y, a*v.z);
}

} //namespace ph

#endif
