#include <SFML/Graphics.hpp>
#include "Noise/noise_texture.h"
#include "Simulation/weather.h"
#include <iostream>
int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1080, 720}), "Terrain Generator");
    sf::RectangleShape fullScreenQuad(sf::Vector2f{ 1080, 720});
    window.setFramerateLimit(144);
    //NoiseTexture noise = NoiseTexture(1080, 720, GeneratorTypes::NG_PERLIN);
    //noise.SetSeed(12);
    WeatherSimulation weatherSim = WeatherSimulation();
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.draw(fullScreenQuad, &weatherSim.weatherShader);
        window.display();
    }
}
