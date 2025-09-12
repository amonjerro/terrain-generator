#include <SFML/Graphics.hpp>

class WeatherSimulation {
public:
	WeatherSimulation();
	void SetNoiseTexture(const sf::Texture& texture);
public:
	sf::Shader weatherShader;
private:
	
};