#include "Primitive.h"

void Primitive::moveTo(const Point &newCenter) {
	Vector translationVec = center - newCenter;
	center = newCenter;
	Transformation T = glm::translate(Transformation(1.0f), translationVec);
	setWorldToObject(worldToObject * T);
}

void Primitive::setWorldToObject(const Transformation &T) {
	worldToObject = T;
	objectToWorld = glm::inverse(T);
}

void Primitive::setObjectToWorld(const Transformation& T) {
	objectToWorld = T;
	worldToObject = glm::inverse(T);
}

bool Primitive::intersect(const Ray& ray, Intersection *result) {
	return false;
}


BRDF Primitive::getBRDF() {
	return material.brdf;
}

void Primitive::setBRDF(BRDF new_brdf) {
	material.brdf = new_brdf;
}

float Primitive::getShiness() {
	return material.shiness;
}

void Primitive::setShiness(float  s) {
	material.shiness = s;
}
