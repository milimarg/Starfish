#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../includes/core/engineCore.hpp"

int main(void)
{
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "3D Engine");
    Engine3D engine(window);

    engine.loadObjectFromFile("./assets/teapot.obj");
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
