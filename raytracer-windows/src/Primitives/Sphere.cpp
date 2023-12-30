#include "Primitives/Sphere.h"

Sphere::Sphere() { center = Point(0.0f, 0.0f,0.0f); radius = 1.0f; }
Sphere::Sphere(Point center, float radius):center(center), radius(radius) {}

void Sphere::moveTo(const Point& newCenter) {
	center = newCenter;
}

bool Sphere::intersect(const Ray& ray, Intersection *result) {
	const Point p = ray.position;
	const Vector d = ray.direction;
	const Point o = center;
	const float r = radius;

	const float a = glm::dot(d, d);
	const float b = 2.0 * (glm::dot(d, p - o));
	const float c = glm::dot(p-o,p-o) - r * r;

	const float delta = b * b - 4 * a * c;

	if (delta >= 0) {
		float root1 = (-b - glm::sqrt(delta)) / (2 * a);
		float root2 = (-b + glm::sqrt(delta)) / (2 * a);
		// check if exist positive root
		float t;
		if (root1 > 0 && root2 > 0) {
			t = glm::min(root1, root2);
		}
		else if (root1 > 0) {
			t = root1;
		}
		else if (root2 > 0) {
			t = root2;
		}
		else {
			return false;
		}

		// save result
		if (result != nullptr) {
			result->dist = t;
			result->hitPosition = p + d * result->dist;
			result->normalVec = glm::normalize(result->hitPosition - o);
			result->hitPrimitive = this;
		}
		return true;
	}
	return false;
}