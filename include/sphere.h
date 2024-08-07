#ifndef SPHERE_H
#define SPHERE_H

#include "ray.h"
#include "surface.h"
#include "vec3d.h"
#include "interval.h"

class sphere : public surface {
 public:
  sphere(const point3d &center, double radius) : center(center), radius(std::fmax(0, radius)) {}

  bool hit(const ray &r, interval ray_t, hit_record &rec) const override;

 private:
  point3d center;
  double radius;
};

#endif
