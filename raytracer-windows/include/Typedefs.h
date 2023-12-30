#pragma once
#include <glm/glm.hpp>

typedef glm::vec3 Point;
typedef glm::vec3 Vector;
typedef  glm::vec3 Vertex; 

typedef glm::vec3 Translation;
typedef glm::mat3 Rotation;

typedef glm::mat4 Transformation;

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

class Color {
public:
	Color() {};
	Color(float r, float g, float b) :r(r), g(g), b(b) {}
	Color(float r, float g, float b, float a):r(r),g(g),b(b),a(a){}
	
	float r = 1.0;
	float g = 1.0;
	float b = 1.0;
	float a = 1.0;

	Color operator+(const Color &c) {
		return Color(r + c.r, g + c.g, b + c.b, 1 - (1 - a) * (1 - c.a));
	}

	Color operator*(const float scale) {
		return Color(r * scale, g * scale, b * scale, a);
	}

	Color operator*(const Color& c) {
		return Color(r * c.r, g * c.g, b*c.b);
	}

	Color& operator+=(const Color& c) {
		r = r + c.r;
		g = g + c.g;
		b = b + c.b;
		a = 1 - (1 - a) * (1 - c.a);
		return *this;
	}
};

struct BRDF {
	Color kd, ks, ka, kr; //diffuse, specular and ambient , reflection coefficient
};

struct Material {
	BRDF brdf;
	float shiness;
};