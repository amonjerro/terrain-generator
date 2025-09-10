#include "noise.h"
#include "../Math/utilfunc.h"

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

PerlinNoise::PerlinNoise(int gridX, int gridY) {
	gridSizeX = gridX;
	gridSizeY = gridY;
}

void PerlinNoise::SetSeed(int seedValue) {
	seed = seedValue;
}

std::vector<int> PerlinNoise::GetConstantVector(int val) {
	int h = val % 4;
	if (h == 0) {
		return std::vector<int>{1, 1};
	}
	else if (h == 1) {
		return std::vector<int>{-1, 1};
	}
	else if (h == 2) {
		return std::vector<int>{-1, -1};
	}
	else {
		return std::vector<int>{1, -1};
	}
}

float PerlinNoise::GetNoiseValue(int x, int y) {
	int lowGridX = x / gridSizeX;
	lowGridX = lowGridX % 256;
	int lowGridY = y / gridSizeY;
	lowGridY = lowGridY % 256;
	int highGridX = lowGridX + 1;
	highGridX = highGridX % 256;
	int highGridY = lowGridY + 1;
	highGridY = highGridY % 256;

	float xF = (x / (float)gridSizeX) - lowGridX;
	float yF = (y / (float)gridSizeY) - lowGridY;

	std::vector<float> topRight = std::vector<float>{ xF - 1.0f, yF - 1.0f };
	std::vector<float> topLeft = std::vector<float>{ xF, yF - 1.0f };
	std::vector<float> botRight = std::vector<float>{ xF - 1.0f, yF };
	std::vector<float> botLeft = std::vector<float>{ xF, yF };

	int valueTopRight = permutation[permutation[highGridX] + highGridY];
	int valueTopLeft = permutation[permutation[lowGridX] + highGridY];
	int valueBottomRight = permutation[permutation[highGridX] + lowGridY];
	int valueBottomLeft = permutation[permutation[lowGridX] + lowGridY];

	float dotTopRight = DotProduct(topRight, GetConstantVector(valueTopRight));
	float dotTopLeft = DotProduct(topLeft, GetConstantVector(valueTopLeft));
	float dotBottomRight = DotProduct(botRight, GetConstantVector(valueBottomRight));
	float dotBottomLeft = DotProduct(botLeft, GetConstantVector(valueBottomLeft));

	float u = Fade(xF);
	float v = Fade(yF);

	return Lerp(u,
		Lerp(v, dotBottomLeft, dotTopLeft),
		Lerp(v, dotBottomRight, dotTopRight));
}
