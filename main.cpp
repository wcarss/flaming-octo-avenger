#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Player {
public:
    Vector2f max_velocity;
    Vector2f min_velocity;
    float acceleration;
    Vector2f velocity;
    Texture texture;
    Sprite sprite;

    Player(float size){
        setPosition(200.f, 200.f);
        max_velocity = Vector2f(15.f, 15.f);
        min_velocity = Vector2f(-15.f, -15.f);
        acceleration = 1.1f;
        if (!texture.loadFromFile("player.png")) {
            cerr<<"Failed to load texture."<<endl;
        }
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setColor(Color::Green);
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    void move(float x, float y) {
        sprite.move(x, y);
    }

    void draw(RenderWindow& window) {
        window.draw(sprite);
    }

    void controls() {
        bool up_keys = Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up);
        bool down_keys = Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down);
        bool left_keys = Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left);
        bool right_keys = Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right);
        if (up_keys) {
            update_velocity(Vector2f(0, -acceleration));
        }
        if (down_keys) {
            update_velocity(Vector2f(0, acceleration));
        }
        if (left_keys) {
            update_velocity(Vector2f(-acceleration, 0));
        }
        if (right_keys) {
            update_velocity(Vector2f(acceleration, 0));
        }
    }

    void update_velocity(Vector2f direction)
    {
        velocity += direction;
        if (velocity.x > max_velocity.x) {
            velocity.x = max_velocity.x;
        }
        if (velocity.x < min_velocity.x) {
            velocity.x = min_velocity.x;
        }
        if (velocity.y > max_velocity.y) {
            velocity.y = max_velocity.y;
        }
        if (velocity.y < min_velocity.y) {
            velocity.y = min_velocity.y;
        }
    }

    void update_position() {
        float min_x_position = 0;
        float max_x_position = 700;
        float min_y_position = 0;
        float max_y_position = 500;

        velocity_falloff(velocity);
        Vector2f new_position(sprite.getPosition() + velocity);

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

        sprite.setPosition(new_position);
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
};

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
        player.update_position();

        window.clear(Color(30,30,30));
        window.draw(rectangle);
        player.draw(window);
        window.display();
    }

    return 0;
}
