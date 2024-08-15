#ifndef VEC3D_H
#define VEC3D_H

#include <cmath>
#include <iostream>

#include "math_utils.h"

class vec3d {
 public:
  double e[3];
  vec3d() : e{0, 0, 0} {}
  vec3d(double x, double y, double z) : e{x, y, z} {}

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  vec3d operator-() const { return vec3d(-e[0], -e[1], -e[2]); }
  double operator[](int i) const { return e[i]; }
  double& operator[](int i) { return e[i]; }

  vec3d& operator+=(const vec3d& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  vec3d& operator*=(double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  vec3d& operator/=(double t) { return *this *= 1 / t; }

  double length() const { return std::sqrt(length_squared()); }

  double length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

  bool near_zero() const {
    auto s = 1e-8;
    return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
  }
  static vec3d random() { return vec3d(random_double(), random_double(), random_double()); }

  static vec3d random(double min, double max) {
    return vec3d(random_double(min, max), random_double(min, max), random_double(min, max));
  }
};

using point3d = vec3d;

inline std::ostream& operator<<(std::ostream& out, const vec3d& v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3d operator+(const vec3d& u, const vec3d& v) {
  return vec3d(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3d operator-(const vec3d& u, const vec3d& v) {
  return vec3d(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3d operator*(const vec3d& u, const vec3d& v) {
  return vec3d(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3d operator*(double t, const vec3d& v) { return vec3d(t * v.e[0], t * v.e[1], t * v.e[2]); }

inline vec3d operator*(const vec3d& v, double t) { return t * v; }

inline vec3d operator/(const vec3d& v, double t) { return (1 / t) * v; }

inline double dot(const vec3d& u, const vec3d& v) { return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2]; }

inline vec3d cross(const vec3d& u, const vec3d& v) {
  return vec3d(u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2], u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3d unit_vector(const vec3d& v) { return v / v.length(); }

inline vec3d random_in_unit_sphere() {
  while (true) {
    vec3d p = vec3d::random(-1, 1);
    if (p.length_squared() < 1) return p;
  }
}

inline vec3d random_unit_vector() { return unit_vector(random_in_unit_sphere()); }

inline vec3d random_outward_vector(vec3d& normal) {
  vec3d on_unit_sphere = random_unit_vector();
  if (dot(on_unit_sphere, normal) > 0) {
    return on_unit_sphere;
  } else {
    return -on_unit_sphere;
  }
}

inline vec3d reflect(const vec3d& v, const vec3d& n) { return v - 2 * dot(v, n) * n; }

#endif
