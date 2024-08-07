#include "surface_list.h"

#include "interval.h"

bool surface_list::hit(const ray& r, interval ray_t, hit_record& rec) const {
  hit_record temp_rec;
  bool hit_anything = false;
  double closest_so_far = ray_t.max;

  for (const auto& surface : surfaces) {
    if (surface->hit(r, ray_t, temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  }

  return hit_anything;
}
