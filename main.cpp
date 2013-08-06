#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Object {
public:
    bool passable;
    Texture texture;
    Sprite sprite;
    FloatRect rect;

    Vector2f setSize(Vector2f size) {
        FloatRect current_bounds = this->sprite.getGlobalBounds();
//        cout<<"current bounds: pos: ("<<current_bounds.left<<", "<<current_bounds.top<<"), size: ("<<current_bounds.width<<","<<current_bounds.height<<")."<<endl;
        float scale_x = size.x / current_bounds.width;
        float scale_y = size.y / current_bounds.height;
        this->sprite.scale(scale_x, scale_y);
        current_bounds = this->sprite.getGlobalBounds();
//        cout<<"current bounds: pos: ("<<current_bounds.left<<", "<<current_bounds.top<<"), size: ("<<current_bounds.width<<","<<current_bounds.height<<")."<<endl;
    }

    Object(String str, Vector2f pos, Vector2f size, bool passable) {
        this->texture.loadFromFile(str);
        this->texture.setRepeated(true);
        this->sprite.setTexture(this->texture);
        this->sprite.setPosition(pos);
        setSize(size);
        //this->sprite.setScale(this->sprite.getGlobalBounds();
        this->passable = passable;
        this->rect = FloatRect(pos, size);
    }
};

class Player {
public:
    Vector2f max_velocity;
    Vector2f min_velocity;
    float acceleration;
    Vector2f velocity;
    Texture texture;
    Sprite sprite;
    Vector2f size;

    Player(float size_x, float size_y) {
        FloatRect bounds_rect;
        this->max_velocity = Vector2f(15.f, 15.f);
        this->min_velocity = Vector2f(-15.f, -15.f);
        this->acceleration = 1.1f;
        if (!texture.loadFromFile("player.png")) {
            cerr<<"Failed to load texture."<<endl;
        }
        this->texture.setSmooth(true);
        this->sprite.setTexture(texture);
        this->sprite.setColor(Color::Green);
        bounds_rect = sprite.getGlobalBounds();
//        cout<<"current bounds: pos: ("<<bounds_rect.left<<", "<<bounds_rect.top<<"), size: ("<<bounds_rect.width<<","<<bounds_rect.height<<")."<<endl;
        this->size = Vector2f(size_x, size_y);
        this->sprite.scale(this->size.x / bounds_rect.height, this->size.y / bounds_rect.width);
        //this->sprite.setOrigin(this->size.x / 2, this->size.y / 2);
        bounds_rect = sprite.getGlobalBounds();
//        cout<<"current bounds: pos: ("<<bounds_rect.left<<", "<<bounds_rect.top<<"), size: ("<<bounds_rect.width<<","<<bounds_rect.height<<")."<<endl;
        setPosition(200.f, 200.f);
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

    void update_position(Object object) {
        float min_x_position = 0;
        float max_x_position = 700;
        float min_y_position = 0;
        float max_y_position = 600;

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

//cout<<"object.passable: "<<object.passable<<"."<<endl;
//cout<<"object.rect: pos: ("<<object.rect.left<<", "<<object.rect.top<<"), size: ("<<object.rect.width<<","<<object.rect.height<<")."<<endl;
//cout<<"new_position: ("<<new_position.x<<", "<<new_position.y<<")."<<endl;
        if (!object.passable && object.rect.intersects(FloatRect(new_position, size))) {
//cout<<"CONTAINS!!!"<<endl;
            new_position = sprite.getPosition();
            velocity.x = 0;
            velocity.y = 0;
        }

        sprite.setPosition(new_position);
        velocity_falloff(velocity);
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
    Player player(100.f, 100.f);
    Object wall("brown.png", Vector2f(0.0f, 550.0f), Vector2f(800.f, 50.f), false);
    Object** objects = new Object*[1];
    objects[0] = &wall;
    //RectangleShape rectangle(Vector2f(800.f, 50.f));
    int key_code;
    //rectangle.setFillColor(Color(100,80,80));
    //rectangle.setPosition(0.0f, 550.0f);

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
        player.update_position(*objects[0]);

        window.clear(Color(30,30,30));
        window.draw(wall.sprite);
        player.draw(window);
        window.display();
    }

    delete objects;
    return 0;
}
