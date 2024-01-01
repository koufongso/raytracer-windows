#include "Primitives/Triangle.h"

Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3) :v1(v1), v2(v2), v3(v3) {
	center = Point(.0f, .0f, .0f);
	normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));
};

void Triangle::moveTo(const Point& newCenter) {
	Vector dv = newCenter - center;
	center = newCenter;
	v1 += dv;
	v2 += dv;
	v3 += dv;
}

bool Triangle::intersect(const Ray& ray, Intersection *result) {
	const Point p = ray.position;
	const Vector d = ray.direction;

	// solve Ax=b where x = [t, beta, gamma]
	// alpha, beta gamma needs to satisfy:
	//		alpha + beta + gamma = 1
	//		0 <=alpha, beta, gamma <=1
	const glm::mat3 A = glm::mat3(-d, v2 - v1, v3 - v1);
	const glm::vec3 b = p - v1;
	const glm::vec3 sol = glm::inverse(A) * b;

	const float beta = sol.y;
	const float gamma = sol.z;
	const float alpha = 1 - beta - gamma;

	if ((alpha >= 0 && alpha <= 1) && (beta >= 0 && beta <= 1) && (gamma >= 0 && gamma <= 1)) {
		const float t = sol.x;
		if (t <= 0) {
			return false;
		}

		if (result != nullptr) {
			result->dist = t;
			result->hitPosition = p + t * d;
			result->outward_normal = glm::dot(normal,ray.direction)>=0? -normal: normal;
			result->hitPrimitive = this;
		}
		return true;
	}
	else {
		return false;
	}

}