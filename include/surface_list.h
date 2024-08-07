#ifndef SURFACE_LIST_H
#define SURFACE_LIST_H

#include <memory>
#include <vector>

#include "interval.h"
#include "surface.h"

using std::make_shared;
using std::shared_ptr;

class surface_list : public surface {
 public:
  std::vector<shared_ptr<surface>> surfaces;

  surface_list() {}
  surface_list(shared_ptr<surface> surface) { add(surface); }

  void clear() { surfaces.clear(); }

  void add(shared_ptr<surface> surface) { surfaces.push_back(surface); }

  bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};

#endif
