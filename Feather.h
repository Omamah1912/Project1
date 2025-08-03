#pragma once
#include "Collectible.h"
#include "Duck.h"

class Feather : public Collectible {
public:
    Feather(float x, float y) {
        if (setTexture("assets/feather.png")) {
            scaleToSize(48.0f, 48.0f); // 32x32 pixels
        }
        setPosition(x, y);
    }

    void onCollect(Duck& duck) override {
        std::cout << "Collected Feather! +10 points" << std::endl;
        duck.addScore(10);
        // Add scoring logic here later
    }
};
