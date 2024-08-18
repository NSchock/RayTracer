#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "math_utils.h"
#include "ray.h"
#include "surface.h"
#include "vec3d.h"

class camera {
 public:
  double aspect_ratio = 1.0;
  int image_width = 100;
  int samples_per_pixel = 10;
  int max_depth = 10;

  double vfov = 90; // vertical view angle
  point3d camera_center{0,0,0};
  point3d look_at{0,0,-1}; // the point the camera center is looking at
  vec3d vup{0,1,0}; // upwards direction from camera center
  
  double defocus_angle = 0;
  double focus_dist = 10;

  void render(const surface& world);

 private:
  int image_height;
  double pixel_samples_scale;
  point3d center;
  point3d pixel00_loc;
  vec3d pixel_delta_hor;
  vec3d pixel_delta_vert;
  vec3d u,v,w; // camera frame basis vectors

  vec3d defocus_disk_hor;
  vec3d defocus_disk_vert;

  void initialize();

  color ray_color(const ray& r, int depth, const surface& world) const;

  /**
   * Get ray from origin to a randomly sampled point near pixel (i,j).
   **/
  ray get_ray(int i, int j) const;

  vec3d sample_square() const { return vec3d(random_double() - 0.5, random_double() - 0.5, 0); }

  point3d defocus_disk_sample() const;
};

#endif
