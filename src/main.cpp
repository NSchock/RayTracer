#include "camera.h"
#include "sphere.h"
#include "surface_list.h"
#include "vec3d.h"

int main() {
  surface_list world;
  world.add(make_shared<sphere>(point3d(0, -100.5, -1), 100));
  world.add(make_shared<sphere>(point3d(0, 0, -1), 0.5));

  camera cam;

  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 400;

  cam.render(world);
}
