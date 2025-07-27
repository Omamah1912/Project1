#pragma once
#include "Enemy.h"

class Bear : public Enemy {
public:
    Bear(float x, float y) {
        setTex("assets/bear.png");
        setPosition(x, y);
    }

    void onCollide() override {
        // Reduce health or reset player
    }
};
