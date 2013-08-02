#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Player {
public:
    Vector2f velocity;
    CircleShape circle;

    Player(float size){
        circle = CircleShape(size);
    }

    void setPosition(float x, float y) {
        circle.setPosition(x, y);
    }

    void move(float x, float y) {
        circle.move(x, y);
    }
};

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
    float max_x_position = 700;
    float min_y_position = 0;
    float max_y_position = 500;
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
    Player player(50.f);
    RectangleShape rectangle(Vector2f(800.f, 50.f));
    bool key_pressed;
    int key_code;
    float acceleration = 0.4f;
    float maximum_velocity = 15.f;
    rectangle.setFillColor(Color(100,80,80));
    rectangle.setPosition(0.0f, 550.0f);
    player.circle.setFillColor(Color::Green);
    player.setPosition(200.f, 200.f);

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
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            change_velocity(player.velocity.y, -acceleration, -maximum_velocity);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            change_velocity(player.velocity.y, acceleration, maximum_velocity);
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            change_velocity(player.velocity.x, -acceleration, -maximum_velocity);
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            change_velocity(player.velocity.x, acceleration, maximum_velocity);
        }

        velocity_falloff(player.velocity);
        update_position(player.circle, player.velocity);

        window.clear(Color(30,30,30));
        window.draw(rectangle);
        window.draw(player.circle);
        window.display();
    }

    return 0;
}
