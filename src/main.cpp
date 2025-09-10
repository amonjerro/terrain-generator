#include <SFML/Graphics.hpp>
#include "Noise/noise_texture.h"
#include <iostream>
int main()
{
    uint16_t width = 640u;
    uint16_t height = 360u;
    auto window = sf::RenderWindow(sf::VideoMode({width, height}), "CMake SFML Project");
    window.setFramerateLimit(144);
    NoiseTexture noise = NoiseTexture(width, height, GeneratorTypes::NG_PERLIN);
    //std::cout << (12 / (float) 10) - (12/10) << std::endl;
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
        window.draw(noise.GetNoiseDrawable());
        window.display();
    }
}
