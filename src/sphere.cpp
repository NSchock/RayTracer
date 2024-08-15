#include "sphere.h"

#include "interval.h"
#include "ray.h"
#include "surface.h"
#include "vec3d.h"

bool sphere::hit(const ray &r, interval ray_t, hit_record &rec) const {
  point3d oc = center - r.origin();
  double a = r.direction().length_squared();
  double h = dot(r.direction(), oc);
  double c = oc.length_squared() - radius * radius;

  // this isn't actually the discriminant; rather it is the discrimant / 4.
  // (using simplified quadratic equation)
  double discriminant = h * h - a * c;
  if (discriminant < 0) {
    return false;
  }

  double sqrtd = std::sqrt(discriminant);
  double root = (h - sqrtd) / a;

  // root is out of admissible bounds
  if (!ray_t.surrounds(root)) {
    // try other root
    root = (h + sqrtd) / a;
    if (!ray_t.surrounds(root)) {
      return false;
    }
  }
  rec.t = root;
  rec.p = r.at(rec.t);
  vec3d outward_normal = (rec.p - center) / radius;
  rec.set_face_normal(r, outward_normal);
  rec.mat = mat;

  return true;
}
