#pragma once
#include <glm/glm.hpp>
#include "Primitives/PrimitiveBase.h"
#include "Typedefs.h"



// 12/26/2023 Gaofeng Su
// ray tracer learning project

class PrimitiveBase;

class Ray
{
public:
	Ray(Point position, Vector direction);
	Ray(Point position, Vector direction, PrimitiveBase* primitive);
	Ray(Point position, Vector dir, float t_min, float t_max);

	Point position;
	Vector direction;
	float t_min = 0;
	float t_max = INFINITY;
	PrimitiveBase* fromPrimitive = nullptr;

};

