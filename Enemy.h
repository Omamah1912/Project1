#pragma once
#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy() {}
    virtual ~Enemy() = default;

    virtual void onCollide() = 0;

    virtual void update(float dt) override {
        // Animation or patrol logic if needed
    }

    virtual void render(sf::RenderWindow& window) override {
        window.draw(sprite);
    }
};
