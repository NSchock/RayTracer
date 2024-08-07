#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "ray.h"
#include "surface.h"

class camera {
 public:
  double aspect_ratio = 1.0;
  int image_width = 100;

  void render(const surface& world);

 private:
  int image_height;
  point3d center;
  point3d pixel00_loc;
  vec3d pixel_delta_hor;
  vec3d pixel_delta_vert;

  void initialize();

  color ray_color(const ray& r, const surface& world) const;
};

#endif
