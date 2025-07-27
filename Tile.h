

#pragma once
#include "Entity.h"

class Tile : public Entity {
private:
    bool textureLoaded = false;
    sf::RectangleShape background;  // Background shape to handle transparency

public:
    Tile(const std::string& texturePath, float x, float y) {
        std::cout << "Creating tile with texture: " << texturePath << " at (" << x << "," << y << ")" << std::endl;

        // Setup background for transparency handling
        background.setSize(sf::Vector2f(64.f, 64.f));
        background.setPosition(x, y);
        
        // Set background color based on tile type
        if (texturePath.find("grass") != std::string::npos) {
            background.setFillColor(sf::Color(135, 206, 235)); // Sky blue to match game background
        } else {
            background.setFillColor(sf::Color::Transparent); // No background for solid tiles
        }

        if (!texture.loadFromFile(texturePath)) {
            std::cout << "ERROR: Failed to load tile texture: " << texturePath << std::endl;
            textureLoaded = false;

            // Create a simple colored rectangle as fallback
            sf::Image fallbackImage;
            fallbackImage.create(64, 64, sf::Color::Green); // Green fallback for visibility
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

        // Always scale to 64x64 regardless of original texture size
        float scaleX = 64.f / texture.getSize().x;
        float scaleY = 64.f / texture.getSize().y;
        sprite.setScale(scaleX, scaleY);

        sprite.setPosition(x, y);
        position = sf::Vector2f(x, y);

        std::cout << "Tile created successfully at (" << x << "," << y << ")" << std::endl;
    }

    void update(float dt) override {
        /* Tiles are static */
    }

    void render(sf::RenderWindow& window) override {
        if (textureLoaded) {
            // Draw background first (for transparency handling)
            window.draw(background);
            // Then draw the sprite on top
            window.draw(sprite);
        }
    }

    bool isValid() const {
        return textureLoaded;
    }
};
