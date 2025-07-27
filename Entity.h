#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>


class Entity {
protected:
    sf::Texture texture;      
    sf::Sprite sprite;      
    sf::Vector2f position;    
    float groundLevel = 500.0f;
    float gravity = 1200.f;


public:
    Entity() {}
    virtual ~Entity() {}


    virtual void setTex(const std::string& path) {
        if (!texture.loadFromFile(path)) {
            std::cerr << "Failed to load texture: " << path << "\n";
        }
        sprite.setTexture(texture);
    }

    virtual void setPosition(float x, float y) {
        position = sf::Vector2f(x, y);
        sprite.setPosition(position);
    }

    virtual sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }


    virtual void update(float dt) = 0;


    virtual void render(sf::RenderWindow& window) = 0;

    virtual sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }
};
