#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(800, 600), "Flaming Octo Avenger!");
    CircleShape shape(50.f);
    shape.setFillColor(Color::Green);
    shape.setPosition(200.0f, 200.0f);
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
                if (key_code == Keyboard::W) {
                    shape.move(0.0f, -1.0f);
                }
                if (key_code == Keyboard::S) {
                    shape.move(0.0f, 1.0f);
                }
                if (key_code == Keyboard::A) {
                    shape.move(-1.0f, 0.0f);
                }
                if (key_code == Keyboard::D) {
                    shape.move(1.0f, 0.0f);
                }
            }
        }

        window.clear(Color(30,30,30));
        window.draw(shape);
        window.display();
    }

    return 0;
}
