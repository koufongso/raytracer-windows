#pragma once
# include "Typedefs.h"

class Sampler
{
public:
	Sampler() {};

	Sample getSample(int px_u, int px_v);
};

