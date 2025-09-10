#include "noise_texture.h"

NoiseTexture::NoiseTexture(int width, int height, GeneratorTypes genType) {
	image = std::unique_ptr<sf::Image>(new sf::Image(sf::Vector2u(width, height)));
	texture = sf::Texture();
	switch (genType) {
	case GeneratorTypes::NG_PERLIN:
		generator = std::unique_ptr<NoiseGenerator>(new PerlinNoise(20, 20));
		break;
	default:
		generator = std::unique_ptr<NoiseGenerator>(new WhiteNoise());
		break;
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
			
			image->setPixel(sf::Vector2u(x,y), sf::Color(noiseValue, noiseValue, noiseValue));
		}
	}
	texture.loadFromImage(*image);
}