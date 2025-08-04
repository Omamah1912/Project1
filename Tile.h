#pragma once
#include "Entity.h"
#include <string>

class Tile : public Entity {
private:
    std::string texturePath;
    bool isLoaded;

public:
    Tile(const std::string& texturePath, float x, float y) : texturePath(texturePath), isLoaded(false) {
        isLoaded = setTexture(texturePath);
        if (isLoaded) {
            setPosition(x, y);
        }
    }

    void update(float dt) override {

    }

    void render(sf::RenderWindow& window) override {
        if (isLoaded) {
            window.draw(sprite);
        }
    }

    bool isValid() const {
        return isLoaded;
    }

    std::string getTextureName() const {
        return texturePath;
    }

    // Helper method to check if this tile can be stood on
    bool isSolid() const {
        return texturePath == "assets/ground.png" || texturePath == "assets/grass.png";
    }


};