// Tornado.h - Fixed
#pragma once
#include "Obstacle.h"

class Tornado : public Obstacle {
public:
    Tornado(float x, float y) {
        if (setTexture("assets/tornado.png")) {
            scaleToSize(80.0f, 120.0f); // 80x120 pixels - tall tornado
        }
        setPosition(x, y);
    }

    void update(float dt) override {
        // Could add rotation animation here later
    }
};