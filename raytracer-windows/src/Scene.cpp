#include "Scene.h"

Scene::Scene() {
	raytracer.light_sources = &light_sources;
	raytracer.objects = &objects;
}

Scene::~Scene() {
	for (LightBase* light_source_ptr : light_sources) {
		delete light_source_ptr;
	}

	for (PrimitiveBase* obj_ptr : objects) {
		delete obj_ptr;
	}
}

void Scene::render() {
	Camera* cam_ref = camera_list[0];
	Film film = Film (cam_ref->width, cam_ref->height);
	for (int i = 0; i < cam_ref->height; i++) {
		for (int j = 0; j < cam_ref->width; j++) {
			// ray in camera coordinate
			Pixel px = Pixel(i, j);
			Ray ray_cam = cam_ref->createRay(Pixel(i, j));
			// convert to world coordinate
			glm::vec4 pos_h = (cam_ref->camToWorld * glm::vec4(ray_cam.position, 1.0f));
			Point pos = Point(pos_h.x, pos_h.y, pos_h.z);
			glm::vec4 dir_h = (cam_ref->camToWorld * glm::vec4(ray_cam.direction, 0.0f));
			Vector dir = Point(dir_h.x, dir_h.y, dir_h.z);
			Ray ray_world = Ray(pos, dir); // ray in world coordinate
			
			Color c = Color(0.0, 0.0, 0.0);
			raytracer.traceRay(ray_world, 0, c);
			film.commit(px, c);
		}
	}

	film.writeImage("test.png");
}