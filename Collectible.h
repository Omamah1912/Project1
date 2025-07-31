#pragma once
#include "Entity.h"

class Duck;
 
class Collectible : public Entity {
public:
    Collectible() {}
    virtual ~Collectible() = default;

    virtual void onCollect(Duck& duck) = 0;

    virtual void update(float dt) override {
        // Optional animations or bobbing
    }

    virtual void render(sf::RenderWindow& window) override {
        window.draw(sprite);
    }
};
