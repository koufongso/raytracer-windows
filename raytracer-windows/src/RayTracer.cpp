#include "RayTracer.h"

void RayTracer::traceRay(const Ray& ray, int depth, Color& color) {
	// current shading logic:
	//1. reflective and transparent material -> trace reflective, refractive ray and multiply by ks, kt using Fresnel (whitted)
	//2. reflective, not transparent material -> trace reflective ray, with some ks multiplier given by material
	//3. not reflective, nor transparent material -> return color (phong) 
	//4. not reflective, but transparent -> not defined, return color (phong)

	if (depth >= MAX_DEPTH) {
		return;
	}

	// check if the ray hit an object
	Intersection result;
	intersectObjects(ray, &result);
	if (result.hitPrimitive == nullptr) {
		// not hitting anything
		return;
	}

	// hit an object
	MaterialBase* hitMaterial = &(result.hitPrimitive->material);
	if (depth == 0) {
		color += Color(0.2f, 0.2f, 0.2f); //ambient
	}
	// compute color from all light source
	Point hitPosition_ = result.hitPosition - ((result.dist * 0.01f) * ray.direction); //move the intersection a little bit above the surface to avoid numerical issue
	// color from shadow ray
	if (light_sources != nullptr) {
		const std::vector<LightBase*> light_source_ref = *light_sources;
		for (LightBase* light_ptr : light_source_ref) {
			Ray ray_shadow = light_ptr->generateRayLight(hitPosition_);	// generate a light ray from the hit position
			Color color_modifier(1.0f, 1.0f, 1.0f);
			if (!intersectOpaqueObjects(ray_shadow, &color_modifier)) {
				// visiable, phong shading 
				Vector hVec = glm::normalize(-ray.direction + ray_shadow.direction); // half vector
				Color diffuse_term = hitMaterial->kd * std::max(glm::clamp(glm::dot(ray_shadow.direction, result.outward_normal), -1.0f, 1.0f), 0.0f);
				//Color specular = brdf.ks * glm::pow(std::max(glm::clamp(glm::dot(hVec, result.outward_normal),-1.0f,1.0f), 0.0f), hitMaterial->shiness);
				color += (diffuse_term * light_ptr->color * color_modifier);
			}
			else {
				//occluded by at lease one opaque object
			}
		}
	}

	Color color_reflect(0.0f, 0.0f, 0.0f);
	if (hitMaterial->isReflective) {
		Vector reflect_dir = glm::reflect(ray.direction, result.outward_normal);
		Ray ray_reflect = Ray(hitPosition_, reflect_dir, ray.fromPrimitive);
		traceRay(ray_reflect, depth + 1, color_reflect);
	}

	Color color_refract(0, 0, 0);
	bool flag_TIR = false;
	float n1 = ray.fromPrimitive != nullptr ? ray.fromPrimitive->material.refractive_index : 1.0f; // indice light refractive index
	float n2 = ray.fromPrimitive == result.hitPrimitive ? 1.0f : result.hitPrimitive->material.refractive_index;
	if (hitMaterial->isTransparent) {
		Point hitPosition_refract = result.hitPosition + ((result.dist * 0.01f) * ray.direction); // avoid numerical issue;
		Vector refract_dir = glm::normalize(glm::refract(-ray.direction, result.outward_normal, n1 / n2));
		flag_TIR = glm::any(glm::isnan(refract_dir));
		if (!flag_TIR) {
			Ray ray_refract = Ray(hitPosition_refract, refract_dir, result.hitPrimitive);
			traceRay(ray_refract, depth + 1, color_refract);
		}
	}

	if (hitMaterial->isReflective && hitMaterial->isTransparent) {
		if (flag_TIR == false) {
			//use Schlick’s	approximation of Fresnel equation
			float kF0 = glm::pow((n2 - n1) / (n1 + n2), 2.0f);
			float ks = kF0 + (1 - kF0) * pow((1 - glm::dot(-ray.direction, result.outward_normal)), 5.0f);
			ks = glm::min(glm::max(ks, 0.0f), 1.0f);
			color += (color_reflect * ks + color_refract * (1 - ks));
			//color += (color_reflect * 0.1 + color_refract * (1 - 0.1));
			return;
		}
		else {
			color += color_reflect;
			return;
		}
	}

	if (hitMaterial->isReflective && !hitMaterial->isTransparent) {
		// material shoudl provide the specular term ks
		color += (color_reflect * hitMaterial->ks);
		return;
	}
}


bool RayTracer::intersectObjects(const Ray& ray) {
	if (objects != nullptr) {
		const std::vector<PrimitiveBase*> objects_ref = *objects;
		for (PrimitiveBase* obj_ptr : objects_ref) {
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
		const std::vector<PrimitiveBase*> objects_ref = *objects;
		for (PrimitiveBase* obj_ptr : objects_ref) {
			Intersection res;
			if ((intersect = obj_ptr->intersect(ray, &res)) && res.dist < min_dist) {
				min_dist = res.dist;
				*result = res;
			}
		}
	}
	return intersect;
}

bool RayTracer::intersectOpaqueObjects(const Ray& ray, Color *color_modifier) {
	if (objects != nullptr) {
		const std::vector<PrimitiveBase*> objects_ref = *objects;
		for (PrimitiveBase* obj_ptr : objects_ref) {
			Intersection res;
			if (obj_ptr->intersect(ray, &res)) {
				if (!res.hitPrimitive->material.isTransparent) {
					return true;
				}
				else {
					*color_modifier *= Color(0.8f,0.8f,0.8f);
				}
			}
		}
	}
	return false;
}



