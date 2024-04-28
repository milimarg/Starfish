#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../includes/core/engineCore.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Command should be: ./starfish <path to obj file>" << std::endl;
        return 1;
    }
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "3D Engine");
    Engine3D engine(window);

    engine.loadObjectFromFile(std::string(argv[1]));
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        engine.update();
        engine.draw();
    }
    return (0);
}
