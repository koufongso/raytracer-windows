#pragma once
#include "LightBase.h"
class PointLight :	public LightBase
{
public:
	PointLight(Point position);
	Ray generateRayLight(Point ray_origin) override;

	Point position;
};

