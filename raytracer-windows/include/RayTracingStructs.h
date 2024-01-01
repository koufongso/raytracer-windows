#pragma once

struct Sample {
	Sample(float u, float v) :u(u), v(v) {};
	float u;
	float v;
};

// top left is (i=1,j=1), bottom right is (i=height, j=width)
struct Pixel {
	Pixel(int i, int j) :i(i), j(j) {};
	int i;
	int j;
};

struct Color {
	Color() { r = 0.0f; g = 0.0f; b = 0.0f; }
	Color(float r, float g, float b) :r(r), g(g), b(b) {}

	Color operator+(const Color& c) {
		return Color(r + c.r, g + c.g, b + c.b);
	}

	Color operator-(const Color& c) {
		return Color(r - c.r, g - c.g, b - c.b);
	}

	Color operator*(const float scale) {
		return Color(r * scale, g * scale, b * scale);
	}

	Color operator*(const Color& c) {
		return Color(r * c.r, g * c.g, b * c.b);
	}

	Color& operator+=(const Color& c) {
		r += c.r;
		g += c.g;
		b += c.b;
		return *this;
	}

	Color& operator*= (const Color & c){
		r *= c.r;
		g *= c.g;
		b *= c.b;
		return *this;
	}

	float r;
	float g;
	float b;
};