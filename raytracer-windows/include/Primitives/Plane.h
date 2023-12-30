#pragma once
#include "PrimitiveBase.h"
#include <glm/glm.hpp>
#include "Typedefs.h"
class Plane :
    public PrimitiveBase
{
public:
    Plane(const Vertex &v1,const Vertex &v2, const Vertex& v3);
    //Plane(const Point& center, const Vector& normal, float h, float w);

    void moveTo(const Point& newCenter) override;
    bool intersect(const Ray& ray, Intersection* result) override;
    
    Vertex v1;
    Vertex v2;
    Vertex v3;

    Point center;
    Vector normal;
};

