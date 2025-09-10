#pragma once

#include <SFML/Graphics.hpp>

enum class GeneratorTypes {
	NG_WHITE_NOISE,
	NG_PERLIN
};


class NoiseTexture {
public:
	explicit NoiseTexture(int width, int height, GeneratorTypes generatorType);
	sf::Shader shader;
};