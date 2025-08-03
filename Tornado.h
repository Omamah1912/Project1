
#pragma once
#include "Obstacle.h"

class Tornado : public Obstacle {
private:
    float baseY;
    float bobTimer;

public:
    Tornado(float x, float y) : baseY(y), bobTimer(0.f) {
        if (setTexture("assets/tornado.png")) {
            scaleToSize(80.0f, 120.0f);
        }
        setPosition(x, y);
    }

    void update(float dt) override {
        // Bobbing animation
        bobTimer += dt;
        float offset = sin(bobTimer * 2.0f) * 5.0f; // ±5px
        setPosition(getPosition().x, baseY + offset);
    }

    bool shouldPushDuck(const sf::Vector2f& duckPos) {
        return getBounds().contains(duckPos);
    }
};
