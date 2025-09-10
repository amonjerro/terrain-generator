#include "utilfunc.h"

float DotProduct(std::vector<int> a, std::vector<int> b) {
	return a[0] * b[0] + a[1] * b[1];
}

float DotProduct(std::vector<float> a, std::vector<int> b) {
	return a[0] * b[0] + a[1] * b[1];
}

float DotProduct(std::vector<float> a, std::vector<float> b) {
	return a[0] * b[0] + a[1] * b[1];
}

float Fade(float t) {
	return ((6 * t - 15) * t + 10) * t * t * t;
}

float Lerp(float t, float min, float max) {
	return min + t * (max - min);
}