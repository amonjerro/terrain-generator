#include "weather.h"

WeatherSimulation::WeatherSimulation() {
	weatherShader = sf::Shader{};
	if (!weatherShader.isAvailable()) {
		// Deal with the fact there is an error here
	}

	if (!weatherShader.loadFromFile("shaders/bands.frag", sf::Shader::Type::Fragment)) {

	}
	weatherShader.setUniform("waveScale", 0.025f);
}

void WeatherSimulation::SetNoiseTexture(const sf::Texture& noiseTex) {
	weatherShader.setUniform("noiseTex", noiseTex);
}