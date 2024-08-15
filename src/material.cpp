#include "material.h"

#include "surface.h"
#include "vec3d.h"

bool lambertian::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
  vec3d scatter_direction = rec.normal + random_unit_vector();
  if (scatter_direction.near_zero()) {
    // in case random_unit_vector points in exactly the opposite direction of rec.normal
    scatter_direction = rec.normal;
  }
  scattered = ray(rec.p, scatter_direction);
  attenuation = whiteness;
  return true;
}

bool metal::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
  vec3d reflected = reflect(r_in.direction(), rec.normal);
  reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
  scattered = ray(rec.p, reflected);
  attenuation = whiteness;
  return (dot(scattered.direction(), rec.normal) > 0);
}
