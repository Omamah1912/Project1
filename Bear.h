#pragma once
#include "Enemy.h"

class Bear : public Enemy {
public:
    Bear(float x, float y) {
        setTex("assets/bear.png");
        setScale(0.3f);  // Make bear smaller and more proportional
        setPosition(x, y);
    }

    void onCollide() override {
        // Reduce health or reset player
    }
};
