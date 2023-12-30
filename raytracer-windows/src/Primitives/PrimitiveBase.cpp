#include "Primitives/PrimitiveBase.h"

void PrimitiveBase::moveTo(const Point &newCenter) {
	Vector translationVec = center - newCenter;
	center = newCenter;
	Transformation T = glm::translate(Transformation(1.0f), translationVec);
	setWorldToObject(worldToObject * T);
}

void PrimitiveBase::setWorldToObject(const Transformation &T) {
	worldToObject = T;
	objectToWorld = glm::inverse(T);
}

void PrimitiveBase::setObjectToWorld(const Transformation& T) {
	objectToWorld = T;
	worldToObject = glm::inverse(T);
}

bool PrimitiveBase::intersect(const Ray& ray, Intersection *result) {
	return false;
}


BRDF PrimitiveBase::getBRDF() {
	return material.brdf;
}

void PrimitiveBase::setBRDF(BRDF new_brdf) {
	material.brdf = new_brdf;
}

float PrimitiveBase::getShiness() {
	return material.shiness;
}

void PrimitiveBase::setShiness(float  s) {
	material.shiness = s;
}
