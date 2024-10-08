#include "camera.h"
#include "material.h"
#include "sphere.h"
#include "surface_list.h"
#include "vec3d.h"

int main() {
  surface_list world;

  auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
  auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
  auto material_left = make_shared<dielectric>(1 / 1.33);
  auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

  world.add(make_shared<sphere>(point3d(0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<sphere>(point3d(0.0, 0.0, -1.2), 0.5, material_center));
  world.add(make_shared<sphere>(point3d(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(make_shared<sphere>(point3d(1.0, 0.0, -1.0), 0.5, material_right));

  camera cam;

  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 400;
  cam.samples_per_pixel = 100;
  cam.max_depth = 50;

  cam.vfov = 90;
  cam.camera_center = point3d(-2, 2, 1);
  cam.look_at = point3d(0, 0, -1);
  cam.vup = vec3d(0, 1, 0);

  cam.defocus_angle = 10.0;
  cam.focus_dist = 3.4;

  cam.render(world);
}
