#pragma once
#include <glm/glm.hpp>
#include "Typedefs.h"
#include "FreeImage.h"
#include <String.h>

class Film
{
public:
	Film(int width, int height);
	~Film();

	void commit(const Pixel& px, const Color& color);
	void writeImage(const char *savepath);

	int width;
	int height;
	uint8_t *image_pixels;
};

