#include "camera.h"

#include "color.h"

void camera::initialize() {
  image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  pixel_samples_scale = 1.0 / samples_per_pixel;

  center = point3d(0, 0, 0);

  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width{viewport_height * (double(image_width) / image_height)};

  vec3d viewport_hor(viewport_width, 0, 0);
  vec3d viewport_vert(0, -viewport_height, 0);

  pixel_delta_hor = viewport_hor / image_width;
  pixel_delta_vert = viewport_vert / image_height;

  point3d viewport_upper_left = center - vec3d(0, 0, focal_length) - viewport_hor / 2.0 - viewport_vert / 2.0;
  pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_hor + pixel_delta_vert);
}

color camera::ray_color(const ray& r, const surface& world) const {
  hit_record rec;
  if (world.hit(r, interval(0.0, infinity), rec)) {
    return 0.5 * (rec.normal + color(1.0, 1.0, 1.0));
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
  return ray(center, pixel_sample - center);
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
        pixel_color += ray_color(r, world);
      }
      write_color(std::cout, pixel_color * pixel_samples_scale);
    }
  }
  std::clog << "\rDone.                 \n";
}
