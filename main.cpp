#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Player {
public:
    float maximum_velocity;
    float acceleration;
    Vector2f velocity;
    CircleShape circle;

    Player(float size){
        circle = CircleShape(size);
        circle.setFillColor(Color::Green);
        setPosition(200.f, 200.f);
        maximum_velocity = 15.f;
        acceleration = 0.4f;
    }

    void setPosition(float x, float y) {
        circle.setPosition(x, y);
    }

    void move(float x, float y) {
        circle.move(x, y);
    }

    void controls() {
        bool up_keys = Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up);
        bool down_keys = Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down);
        bool left_keys = Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left);
        bool right_keys = Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right);
        if (up_keys) {
            change_velocity(velocity.y, -acceleration, -maximum_velocity);
        }
        if (down_keys) {
            change_velocity(velocity.y, acceleration, maximum_velocity);
        }
        if (left_keys) {
            change_velocity(velocity.x, -acceleration, -maximum_velocity);
        }
        if (right_keys) {
            change_velocity(velocity.x, acceleration, maximum_velocity);
        }
    }

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
};

void update_position(CircleShape& shape, Vector2f velocity);
void velocity_falloff(Vector2f& velocity);

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
    int key_code;
    rectangle.setFillColor(Color(100,80,80));
    rectangle.setPosition(0.0f, 550.0f);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
            switch(event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed:
                    key_code = event.key.code;
                    if (key_code == Keyboard::Q || key_code == Keyboard::Escape) {
                        window.close();
                        }
                    break;
            }
        }
        player.controls();

        velocity_falloff(player.velocity);
        update_position(player.circle, player.velocity);

        window.clear(Color(30,30,30));
        window.draw(rectangle);
        window.draw(player.circle);
        window.display();
    }

    return 0;
}
