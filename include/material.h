#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "ray.h"

class hit_record;

class material {
 public:
  virtual ~material() = default;

  virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
    return false;
  }
};

class lambertian : public material {
 public:
  lambertian(const color& whiteness) : whiteness(whiteness) {}

  bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

 private:
  color whiteness;
};

class metal : public material {
 public:
  metal(const color& whiteness, double fuzz) : whiteness(whiteness), fuzz(fuzz < 1 ? fuzz : 1) {}

  bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

 private:
  color whiteness;
  double fuzz;
};

class dielectric : public material {
 public:
  dielectric(double refraction_index) : refraction_index(refraction_index) {}

  bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

 private:
  double refraction_index;

  static double reflectance(double cos, double ref_ind) {
    // Schlick approximation
    double r0 = (1.0 - ref_ind) / (1.0 + ref_ind);
    r0 = r0 * r0;
    return r0 + (1.0 - r0) * std::pow((1.0 - cos), 5);
  }
};

#endif
