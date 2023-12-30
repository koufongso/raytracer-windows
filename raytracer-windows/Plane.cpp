#include "Plane.h"

Plane::Plane(const Vertex& v1, const Vertex& v2, const Vertex& v3): v1(v1),v2(v2),v3(v3) {
	Vector vec1 = v2 - v1;
	Vector vec2 = v3 - v2;
	Vector vec3 = v3 - v1;

	center = v1 + 0.5f * vec3;
	normal = glm::normalize(glm::cross(vec1, vec3));
}


void Plane::moveTo(const Point& newCenter) {
	Vector dv = newCenter - center;
	center = newCenter;
	v1 += dv;
	v2 += dv;
	v3 += dv;
}

bool Plane::intersect(const Ray& ray, Intersection* result) {
	Vector d = ray.direction;
	glm::mat3 A(-d,v2-v1,v3-v2);
	glm::vec3 b = ray.position - v1;
	glm::vec3 sol = glm::inverse(A) * b;

	if (sol.y >= 0 && sol.y <= 1 && sol.z >= 0 && sol.z <= 1 && sol.x>0) {
		if (result != nullptr) {
			result->dist = sol.x;
			result->hitPosition = ray.position + sol.x * ray.direction;
			result->normalVec = normal;
			result->hitPrimitive = this;
		}
		return true;
	}
	else {
		return false;
	}


}
