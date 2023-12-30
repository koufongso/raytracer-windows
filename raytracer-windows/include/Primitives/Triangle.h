#pragma once
#include <glm/glm.hpp>
#include "Typedefs.h"
#include "PrimitiveBase.h"


class Triangle : public PrimitiveBase
{
public:
	Triangle(Vertex v1, Vertex v2, Vertex v3);

	bool intersect(const Ray& ray, Intersection *result);
	void moveTo(const Point& newOrigin) override;

	Vertex v1;
	Vertex v2;
	Vertex v3;
	Vector normal;
};

