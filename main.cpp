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
    float x_speed = 0, y_speed = 0;

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
                    y_speed -= 3;
                }
                if (key_code == Keyboard::S) {
                    y_speed += 3;
                }
                if (key_code == Keyboard::A) {
                    x_speed -= 3;
                }
                if (key_code == Keyboard::D) {
                    x_speed += 3;
                }
                shape.move(x_speed, y_speed);
            }
            x_speed /= 1.2f;
            y_speed /= 1.2f;
            if (x_speed > -0.001 && x_speed < 0.001)
                x_speed = 0;
            if (y_speed > -0.001 && y_speed < 0.001)
                y_speed = 0;
        }

        window.clear(Color(30,30,30));
        window.draw(shape);
        window.display();
    }

    return 0;
}
