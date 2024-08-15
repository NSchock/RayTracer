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

#endif
