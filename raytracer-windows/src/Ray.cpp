#include "Ray.h"

Ray::Ray(Point position, Vector direction) {
	this->position = position;
	this->direction = glm::normalize(direction);
};

Ray::Ray(Point position, Vector direction, PrimitiveBase* primitive) {
	this->position = position;
	this->direction = glm::normalize(direction);
	this->fromPrimitive = primitive;
};

Ray::Ray(Point position, Vector direction, float t_min, float t_max) {
	this->position = position;
	this->direction = glm::normalize(direction);
	this->t_min = t_min;
	this->t_max = t_max;
};




