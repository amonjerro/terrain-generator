#include "noise_texture.h"
#include <random>

NoiseTexture::NoiseTexture(int width, int height, GeneratorTypes genType, int colorize) {
	shader = sf::Shader{};
	if (!shader.isAvailable()) {
		// Shaders not available in this system
	}
	rt = sf::RenderTexture(sf::Vector2u{ (uint16_t)width, (uint16_t)height });
	texWidth = width;
	texHeight = height;
	switch (genType) {
	case GeneratorTypes::NG_PERLIN:
		if (!shader.loadFromFile("shaders/perlin.frag", sf::Shader::Type::Fragment)) {
			// Error loading shader
		}
		//PermutationShuffle();
		shader.setUniform("oct", 4);
		shader.setUniform("frequency", 0.01f);
		shader.setUniform("amplitude", 1.0f);
		shader.setUniformArray("permutation", permutation.data(), permutation.size());
		shader.setUniform("colorize", colorize);
		break;
	//default:
		if (!shader.loadFromFile("shaders/whiteNoise.frag", sf::Shader::Type::Fragment)) {
			// Error loading shader
		}
		shader.setUniform("seed", 1);
		break;
	}
}

void NoiseTexture::SetSeed(int newSeedValue) {
	//shader.setUniform("seed", seed);
	seed = newSeedValue;
	PermutationShuffle();
	shader.setUniformArray("permutation", permutation.data(), permutation.size());
}

void NoiseTexture::PermutationShuffle() {
	std::seed_seq seedSeq{ seed };
	std::mt19937 generator(seed);
	std::uniform_int_distribution distro(0,511);

	for (int i = 0; i < 512; i++) {
		int indexA = distro(generator);
		int indexB = distro(generator);

		int temp = permutation[indexA];
		permutation[indexA] = permutation[indexB];
		permutation[indexB] = temp;
	}
}

void NoiseTexture::GenerateNoise() {
	sf::RectangleShape fullScreenQuad(sf::Vector2f{ (float)texWidth, (float)texHeight });
	rt.clear(sf::Color::Black);
	rt.draw(fullScreenQuad, &shader);
	rt.display();
}

const sf::Texture& NoiseTexture::GetNoiseTexture() {
	return rt.getTexture();
}