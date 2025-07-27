#pragma once
#include "Entity.h"

class Collectible : public Entity {
public:
    Collectible() {}

    virtual void onCollect(Duck& duck) = 0;

    virtual void update(float dt) override {
        // Optional animations or bobbing
    }

    virtual void render(sf::RenderWindow& window) override {
        window.draw(sprite);
    }
};
