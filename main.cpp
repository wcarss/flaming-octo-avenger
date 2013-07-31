#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

void increase_y_velocity(float& y_velocity);
void decrease_y_velocity(float& y_velocity);
void increase_x_velocity(float& x_velocity);
void decrease_x_velocity(float& x_velocity);
void update_position(CircleShape& shape, Vector2f velocity);
void velocity_falloff(Vector2f& velocity);

void increase_y_velocity(float& y_velocity)
{
    float y_acceleration = 1.5;
    float max_y_velocity = 20;
    y_velocity += y_acceleration;
    if (y_velocity > max_y_velocity) {
        y_velocity = max_y_velocity;
    }
}

void decrease_y_velocity(float& y_velocity)
{
    float y_acceleration = 1.5;
    float max_y_velocity = 20;
    y_velocity -= y_acceleration;
    if (y_velocity < -max_y_velocity) {
        y_velocity = -max_y_velocity;
    }
}

void increase_x_velocity(float& x_velocity)
{
    float x_acceleration = 1.5;
    float max_x_velocity = 20;
    x_velocity += x_acceleration;
    if (x_velocity > max_x_velocity) {
        x_velocity = max_x_velocity;
    }
}

void decrease_x_velocity(float& x_velocity)
{
    float x_acceleration = 1.5;
    float max_x_velocity = 20;
    x_velocity -= x_acceleration;
    if (x_velocity < -max_x_velocity) {
        x_velocity = -max_x_velocity;
    }
}

void update_position(CircleShape& shape, Vector2f velocity) {
    float min_x_position = 0;
    float max_x_position = 800;
    float min_y_position = 0;
    float max_y_position = 600;
cout<<"1 shape is ("<<shape.getPosition().x<<","<<shape.getPosition().y<<")"<<endl;
cout<<"velocity is ("<<velocity.x<<","<<velocity.y<<")"<<endl;
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

cout<<"2 shape is ("<<shape.getPosition().x<<","<<shape.getPosition().y<<")"<<endl;
    shape.setPosition(new_position);
cout<<"3 shape is ("<<shape.getPosition().x<<","<<shape.getPosition().y<<")"<<endl;
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
                    increase_y_velocity(velocity.y);
                }
                if (key_code == Keyboard::S) {
                    decrease_y_velocity(velocity.y);
                }
                if (key_code == Keyboard::A) {
                    decrease_x_velocity(velocity.x);
                }
                if (key_code == Keyboard::D) {
                    increase_x_velocity(velocity.x);
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
