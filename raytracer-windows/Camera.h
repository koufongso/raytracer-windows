#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Typedefs.h"
#include "Ray.h"
#include "Sampler.h"
#include "RayTracer.h"

class Camera
{
public:

	Ray createRay(Pixel px); // create a ray for pixel (u,v)

	// set camera pose and image
	void setWorldToCam(const Transformation& T);
	void setCamToWorld(const Transformation &T);
	void setImageSize(const int width,const int height);
	void setFovy(const float fovy);
	
	// given global/world coordinate point, direction, return the worldToCam (and update the w2c and c2w)
	Transformation lootAtDirection(const Vector& dir);
	Transformation lootAtPoint(const Point& center);

	void moveToGlobal(const Point &newEye); // move the camera in the gobla/world coordinate
	// void moveToLocal(const Point &newEye);

	// camera pose
	Point eye = Point(0.0f);
	Vector up = Vector(0.0f,0.0f,1.0f);
	Transformation camToWorld = Transformation(1.0f);
	Transformation worldToCam = glm::inverse(camToWorld);
	
	// image size
	int width;	// [px]
	int height;	// [px]
	float w_half;
	float h_half;
	float aspect;

	// camera setting
	float fovy;
	float fovx;
	float tan_fovy_2;
	float tan_fovx_2;

	Sampler sampler = Sampler();
};

