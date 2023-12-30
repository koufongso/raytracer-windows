#pragma once
#include <vector>
#include "Typedefs.h"
#include "Primitive.h"
#include "Camera.h"
#include "Film.h"
#include "Light.h"
#include "RayTracer.h"

class Scene
{
public:
	Scene();
	~Scene();

	void render();
	
	std::vector<Camera*> camera_list;
	std::vector<Primitive*> objects;
	std::vector<Light*> light_sources;

	RayTracer raytracer;

};

