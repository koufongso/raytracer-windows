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
	if (anti_aliasing) {
		cam_ref->sampler.sample = &Sampler::getSampleRandom;
		sample_per_pixel = sample_per_pixel_anti_aliasing;
	}
	else {
		cam_ref->sampler.sample = &Sampler::getSample;
		sample_per_pixel = 1;
	}
	Film film = Film (cam_ref->width, cam_ref->height);
	for (int i = 0; i < cam_ref->height; i++) {
		for (int j = 0; j < cam_ref->width; j++) {
			// ray in camera coordinate
			Pixel px = Pixel(i, j);
			Color color_final = Color(0, 0, 0);
			for (int k = 0; k < sample_per_pixel; k++) {
				Ray ray_cam = cam_ref->createRay(Pixel(i, j));
				// convert to world coordinate
				glm::vec4 pos_h = (cam_ref->camToWorld * glm::vec4(ray_cam.position, 1.0f));
				Point pos = Point(pos_h.x, pos_h.y, pos_h.z);
				glm::vec4 dir_h = (cam_ref->camToWorld * glm::vec4(ray_cam.direction, 0.0f));
				Vector dir = Point(dir_h.x, dir_h.y, dir_h.z);
				Ray ray_world = Ray(pos, dir); // ray in world coordinate
				Color color_sample = Color(0.0, 0.0, 0.0);
				raytracer.traceRay(ray_world, 0, color_sample);
				color_final += color_sample;
			}
			film.commit(px, color_final*(1.0/sample_per_pixel));
		}
	}

	film.writeImage("test.png");
}