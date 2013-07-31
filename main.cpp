#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Flaming Octo Avenger!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    bool key_pressed;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            key_pressed = event.type == sf::Event::KeyPressed;
            if (key_pressed) {
                if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
