#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Ray.h"
#include "Typedefs.h"

class Primitive;

struct Intersection
{
	Primitive* hitPrimitive = nullptr; // which primitive the ray hit

	float dist;
	Point hitPosition;
	Vector normalVec;
};


class Primitive
{
public:
	virtual bool intersect(const Ray& ray, Intersection *result);
	
	// move object to global/world coordinate
	virtual void moveTo(const Point& newOrigin);

	//virtual void rotateXGlobal(const float deg);
	//virtual void rotateYGlobal(const float deg);
	//virtual void rotateZGlobal(const float deg);
	//
	//virtual void rotateXLocal(const float deg);
	//virtual void rotateYLocal(const float deg);
	//virtual void rotateZLocal(const float deg);

	void setWorldToObject(const Transformation& T);
	void setObjectToWorld(const Transformation& T);

	// material
	BRDF getBRDF();
	void setBRDF(BRDF new_brdf);
	float getShiness();
	void setShiness(float s);
	
	// general properties
	Point center;
	Material material;
	Transformation worldToObject = Transformation(1.0);
	Transformation objectToWorld = Transformation(1.0);


};



