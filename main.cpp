#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

void update_position(CircleShape& shape, Vector2f velocity);
void velocity_falloff(Vector2f& velocity);

void change_velocity(float& velocity, float acceleration=1.5, float limit=20)
{
    velocity += acceleration;
    if (limit > 0 && velocity > limit) {
        velocity = limit;
    }
    if (limit <= 0 && velocity < limit) {
        velocity = limit;
    }
}

void update_position(CircleShape& shape, Vector2f velocity) {
    float min_x_position = 0;
    float max_x_position = 800;
    float min_y_position = 0;
    float max_y_position = 600;
    Vector2f new_position(shape.getPosition() + velocity);

    if (new_position.x > max_x_position) {
        new_position.x = max_x_position;
    }
    if (new_position.x < min_x_position) {
        new_position.x = min_x_position;
    }
    if (new_position.y > max_y_position) {
        new_position.y = max_y_position;
    }
    if (new_position.y < min_y_position) {
        new_position.y = min_y_position;
    }

    shape.setPosition(new_position);
}

void velocity_falloff(Vector2f& velocity) {
    Vector2f falloff(1.1f, 1.1f);
    float velocity_epsilon = 0.01f;
    velocity.x /= falloff.x;
    velocity.y /= falloff.y;
    if (velocity.x > -velocity_epsilon && velocity.x < velocity_epsilon)
        velocity.x = 0;
    if (velocity.y > -velocity_epsilon && velocity.y < velocity_epsilon)
        velocity.y = 0;
}

int main()
{
    RenderWindow window(VideoMode(800, 600), "Flaming Octo Avenger!");
    CircleShape shape(50.f);
    bool key_pressed;
    int key_code;
    Vector2f velocity(0,0);
    shape.setFillColor(Color::Green);
    shape.setPosition(200.0f, 200.0f);

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
                    change_velocity(velocity.y, -1.5, -20);
                }
                if (key_code == Keyboard::S) {
                    change_velocity(velocity.y);
                }
                if (key_code == Keyboard::A) {
                    change_velocity(velocity.x, -1.5, -20);
                }
                if (key_code == Keyboard::D) {
                    change_velocity(velocity.x);
                }
            }
        }

        velocity_falloff(velocity);
        update_position(shape, velocity);

        window.clear(Color(30,30,30));
        window.draw(shape);
        window.display();
    }

    return 0;
}
