#ifndef SURFACE_H
#define SURFACE_H

#include "interval.h"
#include "ray.h"

class hit_record {
 public:
  point3d p;
  vec3d normal;
  double t;
  bool front_facing;  // true means the ray emanates from outside the object

  /**
   * Given a unit length normal vector pointing out of the surface,
   * set the normal vector so it points 'against' the ray.
   * Here two vectors point in the 'same' direction if their dot product is
   *positive, and 'against' each other otherwise. Recall that in 2d, the dot
   *product is positive if the angle between the two vectors is acute. Similarly
   *in 3d, with angle appropriately defined using spherical coordinates.
   **/
  void set_face_normal(const ray& r, const vec3d& outward_normal) {
    front_facing = dot(r.direction(), outward_normal) <= 0.0;
    normal = front_facing ? outward_normal : -outward_normal;
  }
};

class surface {
 public:
  virtual ~surface() = default;

  virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif
