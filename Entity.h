#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


class Entity {
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position;

public:
    Entity() {}
    virtual ~Entity() = default;

    bool setTexture(const std::string& path) {
        if (!texture.loadFromFile(path)) {
            std::cerr << "Failed to load texture: " << path << std::endl;
            return false;
        }
        sprite.setTexture(texture);
        return true;
    }

    void scaleToSize(float targetWidth, float targetHeight) {
        if (texture.getSize().x > 0 && texture.getSize().y > 0) {
            float scaleX = targetWidth / static_cast<float>(texture.getSize().x);
            float scaleY = targetHeight / static_cast<float>(texture.getSize().y);
            sprite.setScale(scaleX, scaleY);
        }
    }

    void setPosition(float x, float y) {
        position = sf::Vector2f(x, y);
        sprite.setPosition(position);
    }

    void setScale(float scaleX, float scaleY) {
        sprite.setScale(scaleX, scaleY);
    }

    sf::Vector2f getPosition() const { return position; }
    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }

    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};