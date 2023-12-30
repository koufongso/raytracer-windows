#include "Film.h"

Film::Film(int width, int height):width(width),height(height) {
	image_pixels = new uint8_t[height*width*3];

	// initialize image color 
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int idx = 3*(width*i + j);
			image_pixels[idx] = 0;			// blue
			image_pixels[idx+1] = 0;		// green
			image_pixels[idx + 2] = 0;	// red
		}
	}
}

Film::~Film() {
	delete[] image_pixels;
}

void Film::commit(const Pixel& px, const Color& color) {
	int idx = 3 * (width * px.i + px.j);
	image_pixels[idx] = 255 * glm::clamp(color.b, 0.0f, 1.0f);			// blue
	image_pixels[idx + 1] = 255 * glm::clamp(color.g, 0.0f, 1.0f);		// green
	image_pixels[idx + 2] = 255 * glm::clamp(color.r, 0.0f, 1.0f);	// red
}

void Film::writeImage(const char* savepath) {
	FreeImage_Initialise();
	FIBITMAP* img = FreeImage_ConvertFromRawBits(image_pixels, width, height, width * 3, 24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, true);
	FreeImage_Save(FIF_PNG, img, savepath, 0);
	FreeImage_Unload(img);
}
