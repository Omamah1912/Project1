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

    // Get appropriate scale for different sprite types
    float getSpriteScale(const std::string& path) {
        if (path.find("rock.png") != std::string::npos) {
            return 1.5f; // Rock is very small (18x63), make it bigger
        }
        else if (path.find("duck_brown.png") != std::string::npos) {
            return 0.4f; // Duck (99x95) - scale down to reasonable size
        }
        else if (path.find("bear.png") != std::string::npos) {
            return 0.08f; // Bear (440x567) - scale down significantly
        }
        else if (path.find("tornado.png") != std::string::npos) {
            return 0.1f; // Tornado (400x624) - scale down significantly
        }
        else if (path.find("feather.png") != std::string::npos) {
            return 0.06f; // Feather (433x577) - scale down significantly
        }
        else if (path.find("juice.png") != std::string::npos) {
            return 0.06f; // Juice (500x500) - scale down significantly
        }
        else if (path.find("seed.png") != std::string::npos) {
            return 0.06f; // Seed (500x500) - scale down significantly
        }
        else if (path.find("puddle.png") != std::string::npos) {
            return 0.08f; // Puddle (500x500) - scale down significantly
        }
        return 1.0f; // Default scale
    }

public:
    Entity() {}
    virtual ~Entity() {}


    virtual void setTex(const std::string& path) {
        if (!texture.loadFromFile(path)) {
            std::cerr << "Failed to load texture: " << path << "\n";
            return;
        }
        sprite.setTexture(texture);
        
        // Apply appropriate scaling
        float scale = getSpriteScale(path);
        sprite.setScale(scale, scale);
        
        std::cout << "Loaded texture: " << path << " with scale: " << scale << std::endl;
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
