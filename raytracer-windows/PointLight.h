#pragma once
#include "Light.h"
class PointLight :	public Light
{
public:
	PointLight(Point position);
	Ray generateRayLight(Point ray_origin) override;

	Color color;
	Point position;
};

