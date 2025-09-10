#pragma once
#include "noise.h"
#include <SFML/Graphics.hpp>

class NoiseTexture {
public:
	explicit NoiseTexture(int width, int height, GeneratorTypes generatorType);
	sf::Sprite GetNoiseDrawable();
	void GenerateNoiseTexture();
private:
	std::unique_ptr<NoiseGenerator> generator;
	std::unique_ptr<sf::Image> image;
	sf::Texture texture;
};