#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Obstacle : public Entity {
public:
    Obstacle() {}

    void update(float dt) override {
        // If obstacles are static, nothing needed.
        // But later, for moving obstacles, override this.
    }

    void render(sf::RenderWindow& window) override {
        window.draw(sprite);
    }
};
