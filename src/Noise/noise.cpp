#include "noise.h"

WhiteNoise::WhiteNoise() {
	seed = 0;
}

float WhiteNoise::GetNoiseValue(int x, int y) {
	std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
	return distribution(generator);
}

void WhiteNoise::SetSeed(int seedValue) {
	seed = seedValue;
	generator = std::mt19937(seed);
}
