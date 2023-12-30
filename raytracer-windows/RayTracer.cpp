#include "RayTracer.h"

void RayTracer::traceRay(const Ray & ray, int depth, Color &color){
	if (depth >= MAX_DEPTH) {
		return;
	}

	// check if the ray hit an object
	Intersection result;
	intersectObjects(ray, &result);
	if (result.hitPrimitive == nullptr) {
		return;
	}

	// hit an object
	// compute color from all light source
	BRDF brdf = result.hitPrimitive->getBRDF();
	if (depth == 0) {
		// primary ray, add ambient light
		color += brdf.ka;
	}

	Point hitPosition_ = result.hitPosition + ((result.dist * 0.001f) * result.normalVec); //move the intersection a little bit above the surface to avoid numerical issue
	if (light_sources != nullptr) {
		const std::vector<Light*> light_source_ref = *light_sources;
		for (Light* light_ptr : light_source_ref) {
			Ray light_ray = light_ptr->generateRayLight(hitPosition_);	// generate a light ray from the hit position
			if (!intersectObjects(light_ray)) {
				// visiable, apply phong reflection model
				// ray is pointing from cam to contact surface, light_ray is pointing from contact surface to light
				Vector hVec = glm::normalize(-ray.direction + light_ray.direction); // half vector
				float shiness = result.hitPrimitive->getShiness();
				Color diffuse = brdf.kd * std::max(glm::clamp(glm::dot(light_ray.direction, result.normalVec),-1.0f,1.0f), 0.0f);
				Color specular = brdf.ks * glm::pow(std::max(glm::clamp(glm::dot(hVec, result.normalVec),-1.0f,1.0f), 0.0f), shiness);

				color += ((diffuse + specular)* light_ptr->color);
			}
			else {
				// block by object, shadow shading
				;
			}
		}
	}

	// reflection
	if (brdf.kr.r > 0 || brdf.kr.g > 0 || brdf.kr.b > 0) {
		Vector reflect_dir = glm::reflect(ray.direction, result.normalVec);
		Ray ray_reflect = Ray(hitPosition_, reflect_dir);
		
		Color color_reflect(0, 0, 0);
		traceRay(ray_reflect, depth+1, color_reflect);
		color += brdf.kr * color_reflect;
	}

	// refraction
}



bool RayTracer::intersectObjects(const Ray& ray) {
	if (objects != nullptr) {
		const std::vector<Primitive*> objects_ref = *objects;
		for (Primitive* obj_ptr : objects_ref) {
			if (obj_ptr->intersect(ray, nullptr)) {
				return true;
			}
		}
	}
	return false;
}

bool RayTracer::intersectObjects(const Ray& ray, Intersection *result) {
	// find the closest intersected object
	float min_dist = INFINITY;
	bool intersect = false;
	if (objects != nullptr) {
		const std::vector<Primitive*> objects_ref = *objects;
		for (Primitive* obj_ptr : objects_ref) {
			Intersection res;
			if ((intersect = obj_ptr->intersect(ray, &res)) && res.dist < min_dist) {
				min_dist = res.dist;
				*result = res;
			}
		}
	}
	return intersect;
}



