#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector direction) {
	this->direction = glm::normalize(direction);
}

Ray DirectionalLight::generateRayLight(Point ray_origin) {
	return Ray(ray_origin, -direction);
}
