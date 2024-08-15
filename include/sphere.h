#ifndef SPHERE_H
#define SPHERE_H

#include <memory>

#include "interval.h"
#include "material.h"
#include "ray.h"
#include "surface.h"
#include "vec3d.h"

class sphere : public surface {
 public:
  sphere(const point3d &center, double radius, std::shared_ptr<material> mat)
      : center(center), radius(std::fmax(0, radius)), mat(mat) {}

  bool hit(const ray &r, interval ray_t, hit_record &rec) const override;

 private:
  point3d center;
  double radius;
  std::shared_ptr<material> mat;
};

#endif
