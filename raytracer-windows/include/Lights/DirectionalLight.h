#pragma once
#include "LightBase.h"
class DirectionalLight : public LightBase
{
public:
	DirectionalLight(Vector direction);
	Ray generateRayLight(Point position) override;

	Vector direction;
};

