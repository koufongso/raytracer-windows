#pragma once
#include <glm/glm.hpp>

#include "Typedefs.h"



// 12/26/2023 Gaofeng Su
// ray tracer learning project



class Ray
{
public:
	Ray(Point position, Vector direction);
	Ray(Point position, Vector dir, float t_min, float t_max);

	Point position;
	Vector direction;
	float t_min = 0;
	float t_max = INFINITY;

};

