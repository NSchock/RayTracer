#include "camera.h"

#include <cmath>

#include "color.h"
#include "material.h"
#include "math_utils.h"
#include "vec3d.h"

void camera::initialize() {
  image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  pixel_samples_scale = 1.0 / samples_per_pixel;

  center = camera_center;

  double theta = degrees_to_radians(vfov);
  double h = std::tan(theta / 2);
  double viewport_height = 2 * h * focus_dist;
  double viewport_width{viewport_height * (double(image_width) / image_height)};

  w = unit_vector(camera_center - look_at);
  u = unit_vector(cross(vup, w));
  v = cross(w, u);

  vec3d viewport_hor = viewport_width * u;
  vec3d viewport_vert = viewport_height * (-v);

  pixel_delta_hor = viewport_hor / image_width;
  pixel_delta_vert = viewport_vert / image_height;

  point3d viewport_upper_left = center - (focus_dist * w) - viewport_hor / 2.0 - viewport_vert / 2.0;
  pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_hor + pixel_delta_vert);

  double defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
  defocus_disk_hor = u * defocus_radius;
  defocus_disk_vert = v * defocus_radius;
}

color camera::ray_color(const ray& r, int depth, const surface& world) const {
  if (depth <= 0) {
    return color(0, 0, 0);
  }
  hit_record rec;
  if (world.hit(r, interval(0.0001, infinity), rec)) {
    ray scattered;
    color attenuation;
    if (rec.mat->scatter(r, rec, attenuation, scattered)) {
      return attenuation * ray_color(scattered, depth - 1, world);
    }
    return color(0, 0, 0);
  }

  vec3d unit_dir{unit_vector(r.direction())};
  double a = 0.5 * (unit_dir.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

ray camera::get_ray(int i, int j) const {
  // we represent pixel (i,j) as the region
  // i-0.5 <= x <= i+0.5, j-0.5 <= y <= j+0.5
  // (offset controls the precise region)
  // This just returns the ray to a random point in this region
  // TODO: I really shouldn't do this---"a pixel is not a little square" (A. Smith)
  // Should update to a more careful method
  vec3d offset = sample_square();
  point3d pixel_sample = pixel00_loc + (i + offset.x()) * pixel_delta_hor + (j + offset.y()) * pixel_delta_vert;

  point3d ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
  return ray(ray_origin, pixel_sample - center);
}

void camera::render(const surface& world) {
  initialize();

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
  for (int j = 0; j < image_height; ++j) {
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      color pixel_color(0, 0, 0);
      for (int sample = 0; sample < samples_per_pixel; sample++) {
        ray r = get_ray(i, j);
        pixel_color += ray_color(r, max_depth, world);
      }
      write_color(std::cout, pixel_color * pixel_samples_scale);
    }
  }
  std::clog << "\rDone.                 \n";
}

point3d camera::defocus_disk_sample() const {
  point3d p = random_in_unit_disk();
  return center + (p[0] * defocus_disk_hor) + (p[1] * defocus_disk_vert);
}
