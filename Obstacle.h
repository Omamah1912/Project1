#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Obstacle : public Entity {
public:
    Obstacle() = default;
    virtual ~Obstacle() override = default;

    void update(float dt) override {

    }

    void render(sf::RenderWindow& window) override {
        window.draw(sprite);
    }
};
