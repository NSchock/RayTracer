#include "material.h"

#include <cmath>

#include "math_utils.h"
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

bool dielectric::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
  attenuation = color(1.0, 1.0, 1.0);
  double ref_ind = rec.front_facing ? (1.0 / refraction_index) : refraction_index;

  vec3d unit_dir = unit_vector(r_in.direction());
  // TODO: cos_theta calculation is repeated in the refract function. Should refactor to remove.
  double cos_theta = std::fmin(dot(-unit_dir, rec.normal), 1.0);
  double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

  vec3d direction;
  if (ref_ind * sin_theta > 1.0 || reflectance(cos_theta, ref_ind) > random_double()) {
    direction = reflect(unit_dir, rec.normal);
  } else {
    direction = refract(unit_dir, rec.normal, ref_ind);
  }

  scattered = ray(rec.p, direction);
  return true;
}
