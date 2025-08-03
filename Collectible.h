#pragma once
#include "Entity.h"

class Duck;
 
class Collectible : public Entity {
private:
    int score = 0;
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
