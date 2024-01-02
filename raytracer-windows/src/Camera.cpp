#include "Camera.h"

// move camera to the new position (in world coordinate)
void Camera::moveToGlobal(const Point& newEye) {
	Vector translationVec = eye-newEye;
	eye = newEye;
	Transformation T = glm::translate(Transformation(1.0f), translationVec);
	setWorldToCam(worldToCam*T);
}

Ray Camera::createRay(Pixel px) {

	Sample sample = this->sampler.sample(px.j, px.i);

	Point p;
	p.x = (sample.u - w_half) * tan_fovx_2 / w_half;
	p.y = (h_half - sample.v) * tan_fovy_2 / h_half;
	p.z = -1;

	Vector rayDirection = glm::normalize(p - Point(0.0)); // camera position at origin of camera coordinate
	return Ray(Point(0.0f), rayDirection);
}

void Camera::setCamToWorld(const Transformation& T) {
	camToWorld = T;
	worldToCam = glm::inverse(T);
}

void Camera::setWorldToCam(const Transformation& T) {
	worldToCam = T;
	camToWorld = glm::inverse(T);
}

void Camera::setImageSize(const int w, const int h){
	width = w;
	height = h;
	w_half = w/2;
	h_half = h/2;
	aspect = static_cast<float>(w) / h;
}

void Camera::setFovy(const float deg){
	float rad = glm::radians(deg);
	fovy = rad;
	tan_fovy_2 = glm::tan(rad / 2.0f);
	tan_fovx_2 = tan_fovy_2*aspect;
}


// given a direction (from camera), update and return the camToWorld transformation
Transformation Camera::lootAtDirection(const Vector& dir) {
	Vector w = glm::normalize(-dir);
	Vector u = glm::cross(up, w);
	Vector v = glm::cross(w, u);

	// update transformation
	setWorldToCam(glm::transpose(Transformation(u.x, u.y, u.z, -u.x * eye.x - u.y * eye.y - u.z * eye.z,
												v.x, v.y, v.z, -v.x * eye.x - v.y * eye.y - v.z * eye.z,
												w.x, w.y, w.z, -w.x * eye.x - w.y * eye.y - w.z * eye.z,
												0.0f, 0.0f, 0.0f, 1.0f)));

	return worldToCam;
}

// given a point to look at, update and return the camToWorld transformation
Transformation Camera::lootAtPoint(const Point& center) {
	return lootAtDirection(center - eye);
}