#include <SFML/Graphics.hpp>
#include "Noise/noise_texture.h"

int main()
{
    uint16_t width = 640u;
    uint16_t height = 360u;
    auto window = sf::RenderWindow(sf::VideoMode({width, height}), "CMake SFML Project");
    window.setFramerateLimit(144);
    NoiseTexture noise = NoiseTexture(width, height, GeneratorTypes::NG_WHITE_NOISE);

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
