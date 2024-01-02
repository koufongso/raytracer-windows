#pragma once
#include <vector>
#include "Typedefs.h"
#include "Primitives/PrimitiveBase.h"
#include "Camera.h"
#include "Film.h"
#include "Lights/LightBase.h"
#include "RayTracer.h"

class Scene
{
public:
	Scene();
	~Scene();

	void render();
	
	std::vector<Camera*> camera_list;
	std::vector<PrimitiveBase*> objects;
	std::vector<LightBase*> light_sources;

	RayTracer raytracer;
	bool anti_aliasing = false;
	int sample_per_pixel = 1;
	int sample_per_pixel_anti_aliasing = 3;

};

