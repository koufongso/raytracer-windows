#pragma once
# include "Typedefs.h"
# include "RayTracingStructs.h"

class Sampler
{
public:
	Sampler() {};

	Sample getSample(int px_u, int px_v);
};

