#pragma once
#include "Light.h"
class DirectionalLight : public Light
{
public:
	DirectionalLight(Vector direction);
	Ray generateRayLight(Point position) override;

	Color color;
	Vector direction;
};

