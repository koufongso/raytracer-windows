#pragma once
#include <glm/glm.hpp>
#include "Primitive.h"
#include "Typedefs.h"
class Sphere : public Primitive
{
public:
	Sphere();
	Sphere(Point center, float radius);

	bool intersect(const Ray& ray, Intersection  *result);
	void moveTo(const Point& newCenter) override;

	Point center;
	float radius;
};

