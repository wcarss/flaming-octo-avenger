#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(800, 600), "Flaming Octo Avenger!");
    CircleShape shape(50.f);
    shape.setFillColor(Color::Green);
    bool key_pressed;
    int key_code;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
            key_pressed = event.type == Event::KeyPressed;
            if (key_pressed) {
                key_code = event.key.code;
                if (key_code == Keyboard::Q || key_code == Keyboard::Escape) {
                    window.close();
                }
            }
        }

        window.clear(Color(30,30,30));
        window.draw(shape);
        window.display();
    }

    return 0;
}
