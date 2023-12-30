#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "Typedefs.h"
#include "Ray.h"
#include "Primitive.h"
#include "Light.h"


class RayTracer
{
public:	
	void traceRay(const Ray& ray, int depth, Color &color);

	// some helper function
	bool intersectObjects(const Ray& ray);								// check if a ray hit an object in the ob
	bool intersectObjects(const Ray& ray, Intersection *ressult);		// check if a ray hit an object and return the result

	int MAX_DEPTH = 3;
	std::vector<Light*> *light_sources;
	std::vector<Primitive*> *objects;

};

