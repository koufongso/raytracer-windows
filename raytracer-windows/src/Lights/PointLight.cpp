#include "Lights/PointLight.h"

PointLight::PointLight(Point position) :position(position) {};

Ray PointLight::generateRayLight(Point ray_origin) {
	Vector vec = position - ray_origin;
	Vector dir = glm::normalize(vec);
	float t_max = glm::length(vec);
	return Ray(ray_origin, dir, 0 ,t_max);
}