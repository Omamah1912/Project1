

#pragma once
#include "Entity.h"

class Tile : public Entity {
private:
    bool textureLoaded = false;
    std::string spriteType;

    // Define appropriate sizes for different sprite types
    float getTargetSize(const std::string& texturePath) {
        if (texturePath.find("ground.png") != std::string::npos) {
            return 32.0f; // Ground tiles should be smaller for better platforming
        }
        else if (texturePath.find("grass.png") != std::string::npos) {
            return 32.0f; // Grass tiles same as ground
        }
        else if (texturePath.find("checkpoint.png") != std::string::npos) {
            return 48.0f; // Checkpoints slightly larger
        }
        return 32.0f; // Default size
    }

public:
    Tile(const std::string& texturePath, float x, float y) {
        std::cout << "Creating tile with texture: " << texturePath << " at (" << x << "," << y << ")" << std::endl;
        spriteType = texturePath;

        if (!texture.loadFromFile(texturePath)) {
            std::cout << "ERROR: Failed to load tile texture: " << texturePath << std::endl;
            textureLoaded = false;

            // Create a simple colored rectangle as fallback
            sf::Image fallbackImage;
            fallbackImage.create(32, 32, sf::Color::Green); // Smaller fallback
            if (!texture.loadFromImage(fallbackImage)) {
                std::cout << "ERROR: Even fallback texture creation failed!" << std::endl;
                return;
            }
            textureLoaded = true;
        }
        else {
            textureLoaded = true;
            std::cout << "Successfully loaded texture: " << texturePath << std::endl;
        }

        sprite.setTexture(texture);

        // Use appropriate scaling based on sprite type
        float targetSize = getTargetSize(texturePath);
        float scaleX = targetSize / texture.getSize().x;
        float scaleY = targetSize / texture.getSize().y;
        sprite.setScale(scaleX, scaleY);

        sprite.setPosition(x, y);
        position = sf::Vector2f(x, y);

        std::cout << "Tile created successfully at (" << x << "," << y << ") with scale: " << scaleX << "x" << scaleY << std::endl;
    }

    void update(float dt) override {
        /* Tiles are static */
    }

    void render(sf::RenderWindow& window) override {
        if (textureLoaded) {
            window.draw(sprite);
        }
    }

    bool isValid() const {
        return textureLoaded;
    }
};
