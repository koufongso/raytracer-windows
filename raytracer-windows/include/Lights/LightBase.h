#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "Ray.h"
#include "Typedefs.h"

class LightBase
{
public:
	virtual Ray generateRayLight(Point position) { 
		std::cout << "Light virual method\n";
		return Ray(Point(0.0), Vector(0));
	};
	Color color;
};

