#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "Typedefs.h"
#include "Ray.h"
#include "Primitives/PrimitiveBase.h"
#include "Lights/LightBase.h"


class RayTracer
{
public:	
	void traceRay(const Ray& ray, int depth, Color &color);

	// some helper function
	bool intersectObjects(const Ray& ray);								// check if a ray hit an object in the ob
	bool intersectObjects(const Ray& ray, Intersection *result);		// check if a ray hit an object and return the result
	bool intersectOpaqueObjects(const Ray& ray, Color *color_modifier);	// check if a shadow ray is occluded

	int MAX_DEPTH = 5;
	std::vector<LightBase*> *light_sources;
	std::vector<PrimitiveBase*> *objects;

};

