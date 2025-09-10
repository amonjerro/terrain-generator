#include <SFML/Graphics.hpp>
#include "Noise/noise_texture.h"
#include <iostream>
int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({640, 360}), "CMake SFML Project");
    sf::RectangleShape fullScreenQuad(sf::Vector2f{ 640, 360 });
    window.setFramerateLimit(144);
    NoiseTexture noise = NoiseTexture(640, 360, GeneratorTypes::NG_PERLIN);

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
        window.draw(fullScreenQuad, &noise.shader);
        window.display();
    }
}
