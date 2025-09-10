#include "noise_texture.h"
#include <iostream>

NoiseTexture::NoiseTexture(int width, int height, GeneratorTypes genType) {
	image = std::unique_ptr<sf::Image>(new sf::Image(sf::Vector2u(width, height)));
	texture = sf::Texture();
	switch (genType) {
	default:
		generator = std::unique_ptr<NoiseGenerator>(new WhiteNoise());
	}
	GenerateNoiseTexture();
}

sf::Sprite NoiseTexture::GetNoiseDrawable() {
	sf::Sprite sprite(texture);
	return sprite;
}

void NoiseTexture::GenerateNoiseTexture() {
	sf::Vector2u dimensions = image->getSize();
	for (int x = 0; x < dimensions.x; x++) {
		for (int y = 0; y < dimensions.y; y++) {
			float noiseValue = generator->GetNoiseValue(x, y) * 256.0f;
			//std::cout << noiseValue << std::endl;
			image->setPixel(sf::Vector2u(x,y), sf::Color(noiseValue, noiseValue, noiseValue));
		}
	}
	texture.loadFromImage(*image);
}