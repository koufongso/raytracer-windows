#pragma once
#include <random>
#include "Typedefs.h"
#include "RayTracingStructs.h"

class Sampler
{
public:
	Sampler() { sample = &getSample; }
	
	Sample(*sample)(const int px_u, const int px_v);
	static Sample getSample(const int px_u, const int px_v);
	static Sample getSampleRandom(const int px_u, const int px_v);
	
};

