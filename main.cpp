#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace sf;
using namespace std;

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

class Collision {
public:
    bool middle;
    bool top;
    bool bottom;
    bool left;
    bool right;

    Collision (bool middle, bool top, bool bottom, bool left, bool right) {
        this->middle = middle;
        this->top = top;
        this->bottom = bottom;
        this->left = left;
        this->right = right;
        // topleft, topright, bottomleft, bottomright would all be easy to do
    }

    bool any() {
        return this->middle || this->top || this->bottom || this->left || this->right;
    }

    bool none() {
        return !(this->any());
    }
};

class Object {
public:
    bool passable;
    Texture texture;
    Sprite sprite;
    FloatRect middle;
    FloatRect top;
    FloatRect bottom;
    FloatRect left;
    FloatRect right;
    string name;

    void setSize(Vector2f size) {
        FloatRect current_bounds = this->sprite.getGlobalBounds();
        float scale_x = size.x / current_bounds.width;
        float scale_y = size.y / current_bounds.height;
        this->sprite.scale(scale_x, scale_y);
        current_bounds = this->sprite.getGlobalBounds();
    }

    Object(String name, String str, Vector2f pos, Vector2f size, bool passable) {
        this->texture.loadFromFile(String("images/") + str);
        this->texture.setRepeated(true);
        this->texture.setSmooth(true);
        this->sprite.setTexture(this->texture);
        this->sprite.setPosition(pos);
        this->passable = passable;
        setSize(size);
        this->middle = FloatRect(pos, size);
        this->top = FloatRect(pos, Vector2f(size.x, 1));
        this->bottom = FloatRect(Vector2f(pos.x, pos.y + (size.y - 1)), Vector2f(size.x, 1));
        this->left = FloatRect(pos, Vector2f(1, size.y));
        this->right = FloatRect(Vector2f(pos.x + size.x, pos.y), Vector2f(1, size.y));
    }

    Collision collides(FloatRect rect) {
        bool middle = false;
        bool top = false;
        bool bottom = false;
        bool left = false;
        bool right = false;
        if (rect.intersects(this->middle)) {
            middle = true;
        }
        if (rect.intersects(this->top)) {
            top = true;
        }
        if (rect.intersects(this->bottom)) {
            bottom = true;
        }
        if (rect.intersects(this->left)) {
            left = true;
        }
        if (rect.intersects(this->right)) {
            right = true;
        }
        return Collision(middle, top, bottom, left, right);
    }

    void draw(RenderWindow& window) {
        window.draw(sprite);
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
        if (!texture.loadFromFile("images/player.png")) {
            cerr<<"Failed to load texture."<<endl;
        }
        this->texture.setSmooth(true);
        this->sprite.setTexture(texture);
        this->sprite.setColor(Color::Green);
        bounds_rect = sprite.getGlobalBounds();
        this->size = Vector2f(size_x, size_y);
        this->sprite.scale(this->size.x / bounds_rect.height, this->size.y / bounds_rect.width);
        bounds_rect = sprite.getGlobalBounds();
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

    void update_position(vector<Object *> objects) {
        float min_x_position = -8000;
        float max_x_position = 8000;
        float min_y_position = -8000;
        float max_y_position = 8000;
        int i = 0;
        Object* object;

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

        for (vector<Object *>::iterator it = objects.begin(); it != objects.end(); ++it) {
            object = *it;
            if (!object->passable && object->collides(FloatRect(new_position, size)).any()) {
                new_position = sprite.getPosition();
                velocity.x = 0;
                velocity.y = 0;
            }
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

bool to_bool(String s) {
    return s == String("true");
}

Object* object_from_str(string str) {
    vector<string> substrings;
    substrings = split(str, ',', substrings);

    String name = String(substrings[0]);
    String file = String(substrings[1]);

    for (vector<string>::iterator it = substrings.begin(); it != substrings.end(); ++it) {
        /* This, shockingly, strips whitespace off of the ends of strings. */
        std::stringstream trimmer;
        trimmer << *it;
        (*it).clear();
        trimmer >> *it;
    }

    Object *object = new Object(String(substrings[0]), String(substrings[1]), Vector2f(atof(substrings[2].c_str()), atof(substrings[3].c_str())), Vector2f(atof(substrings[4].c_str()), atof(substrings[5].c_str())), to_bool(substrings[6]));
    return object;
}

vector<Object *> read_objects(string s) {
    ifstream file ("objects.txt");
    string str;
    vector<Object *> objects;

    if (file.is_open()) {
        while (file.good()) {
            getline(file, str);
            if (str != "") {
                objects.push_back(object_from_str(str));
            }
        }
        file.close();
    }
    return objects;
}

int main() {
    RenderWindow window(VideoMode(800, 600), "Flaming Octo Avenger!");
    View view = window.getDefaultView();
    Player player(90.f, 90.f);
    int key_code;
    vector<Object *> objects = read_objects("objects.txt");

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
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
//        view.rotate(0.1);
        view.setCenter(player.sprite.getPosition());
        window.setView(view);
        player.update_position(objects);

        window.clear(Color(4,4,4));
        for (vector<Object *>::iterator it = objects.begin(); it != objects.end(); it++) {
            (*it)->draw(window);
        }
        player.draw(window);
        window.display();
    }
    //delete objects;
    return 0;
}
