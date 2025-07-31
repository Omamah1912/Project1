#pragma once
#include "Enemy.h"

class Bear : public Enemy {
public:
    Bear(float x, float y) {
        if (setTexture("assets/bear.png")) {
            scaleToSize(64.0f, 64.0f); // 64x64 pixels - larger enemy
        }
        setPosition(x, y);
    }

    void onCollide() override {
        std::cout << "Duck hit Bear! -20 points" << std::endl;
        // Add damage/scoring logic here later
    }
};