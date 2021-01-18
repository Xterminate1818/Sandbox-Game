#include "util.h"

float clamp(float min, float max, float val) {
	return fmax(min, fmin(val, max));
}

int clamp(int min, int max, int val) {
	return fmax(min, fmin(val, max));
}

float magnitude(Vector2f vec) {
	return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

Vector2f normalize(Vector2f vec) {
	float mag = magnitude(vec);
	if (vec.x != 0) vec.x /= mag;
	if (vec.y != 0) vec.y /= mag;
	return vec;
}

Vector2f lerp(Vector2f start, Vector2f end, float percent) {
	percent = clamp(0.f, 1.f, percent);
	Vector2f result = (start + percent * (end - start));
	
	if (-0.1 < result.x && result.x < 0.1) result.x = 0.f;
	if (-0.1 < result.y && result.y < 0.1) result.y = 0.f;

	return result;
}


float lerp(float start, float end, float percent) {
	percent = clamp(0.f, 1.f, percent);
	float result = (start + percent * (end - start));
	if (-0.1f < result && result < 0.1f) result = 0.f;
	return result;
}

Color lerp(Color start, Color end, float percent) {
	percent = clamp(0.f, 1.f, percent);
	Color result;
	result.r = start.r + percent * (end.r - start.r);
	result.g = start.g + percent * (end.g - start.g);
	result.b = start.b + percent * (end.b - start.b);
	result.a = start.a + percent * (end.a - start.a);
	return result;
}
