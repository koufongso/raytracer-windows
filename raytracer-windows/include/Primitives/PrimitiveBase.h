#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Ray.h"
#include "../Typedefs.h"
#include "../Materials/MaterialBase.h"

class PrimitiveBase;
class Ray;

struct Intersection
{
	PrimitiveBase* hitPrimitive = nullptr; // which primitive the ray hit

	float dist;
	Point hitPosition;
	Vector outward_normal; // always point against the ray direction 
};


class PrimitiveBase
{
public:
	virtual bool intersect(const Ray& ray, Intersection* result);
	//virtual bool intersect(const Ray& ray, Intersection *result);
	
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
	
	// general properties
	Point center;
	MaterialBase material;
	Transformation worldToObject = Transformation(1.0);
	Transformation objectToWorld = Transformation(1.0);


};



