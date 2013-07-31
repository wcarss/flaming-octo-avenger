#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Flaming Octo Avenger!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    bool key_pressed;
    int key_code;

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
                key_code = event.key.code;
                if (key_code == sf::Keyboard::Q || key_code == sf::Keyboard::Escape) {
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
