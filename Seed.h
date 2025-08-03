#pragma once
#include "Collectible.h"
#include "Duck.h"

class Seed : public Collectible {
public:
    Seed(float x, float y) {
        if (setTexture("assets/seed.png")) {
            scaleToSize(48.0f, 48.0f); // 24x24 pixels
        }
        setPosition(x, y);
    }

    void onCollect(Duck& duck) override {
        std::cout << "Collected Seed! +5 points" << std::endl;
        duck.addScore(5);
    }
};
