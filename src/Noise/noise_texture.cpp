#include "noise_texture.h"

NoiseTexture::NoiseTexture(int width, int height, GeneratorTypes genType) {
	shader = sf::Shader{};
	if (!shader.isAvailable()) {
		// Shaders not available in this system
	}
	switch (genType) {
	case GeneratorTypes::NG_PERLIN:
		if (!shader.loadFromFile("shaders/perlin.frag", sf::Shader::Type::Fragment)) {
			// Error loading shader
		}
		shader.setUniform("oct", 4);
		shader.setUniform("frequency", 0.01f);
		shader.setUniform("amplitude", 1.0f);

		break;
	//default:
		if (!shader.loadFromFile("shaders/whiteNoise.frag", sf::Shader::Type::Fragment)) {
			// Error loading shader
		}
		break;
	}

}