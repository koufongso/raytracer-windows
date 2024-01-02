#include "Sampler.h"

// sample the ray at the center of the pixel
Sample Sampler::getSample(const int px_u, const int px_v) {	
	const float offset_u = -0.5; // where to sample along camera x axis: -1:left of the pixel, -0.5:center, 0:right
	const float offset_v = 0.5; // where to sample along camera y axis: 1:top of the pixel, 0.5:center, 0:bottom;
	return Sample(px_u + offset_u, px_v - offset_v);
}

Sample Sampler::getSampleRandom(const int px_u, const int px_v) {
	std::random_device rd;
	std::uniform_real_distribution<float> dist(0.0, 1.0);
	
	const float offset_u = -dist(rd); // where to sample along camera x axis: -1:left of the pixel, -0.5:center, 0:right
	const float offset_v = dist(rd); // where to sample along camera y axis: 1:top of the pixel, 0.5:center, 0:bottom;
	return Sample(px_u + offset_u, px_v - offset_v);
}
