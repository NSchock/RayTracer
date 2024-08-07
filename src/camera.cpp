#include "camera.h"

#include "color.h"

void camera::render(const surface& world) {
  initialize();

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
  for (int j = 0; j < image_height; ++j) {
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      point3d pixel_center = pixel00_loc + (i * pixel_delta_hor) + (j * pixel_delta_vert);
      vec3d ray_direction = pixel_center - center;
      ray r{center, ray_direction};
      color pixel_color{ray_color(r, world)};
      write_color(std::cout, pixel_color);
    }
  }
  std::clog << "\rDone.                 \n";
}

void camera::initialize() {
  image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

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
  if (world.hit(r, interval(0, +infinity), rec)) {
    return 0.5 * (rec.normal + color(1.0, 1.0, 1.0));
  }

  vec3d unit_dir{unit_vector(r.direction())};
  double a = 0.5 * (unit_dir.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}
