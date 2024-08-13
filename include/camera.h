#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "math_utils.h"
#include "ray.h"
#include "surface.h"

class camera {
 public:
  double aspect_ratio = 1.0;
  int image_width = 100;
  int samples_per_pixel = 10;

  void render(const surface& world);

 private:
  int image_height;
  double pixel_samples_scale;
  point3d center;
  point3d pixel00_loc;
  vec3d pixel_delta_hor;
  vec3d pixel_delta_vert;

  void initialize();

  color ray_color(const ray& r, const surface& world) const;

  /**
  * Get ray from origin to a randomly sampled point near pixel (i,j).
  **/
  ray get_ray(int i, int j) const;

  vec3d sample_square() const {
    return vec3d(random_double() - 0.5, random_double() - 0.5, 0);
  }
};

#endif
