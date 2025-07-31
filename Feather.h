#pragma once
#include "Collectible.h"
#include "Duck.h"

class Feather : public Collectible {
public:
    Feather(float x, float y) {
        if (setTexture("assets/feather.png")) {
            scaleToSize(32.0f, 32.0f); // 32x32 pixels
        }
        setPosition(x, y);
    }

    void onCollect(Duck& duck) override {
        std::cout << "Collected Feather! +10 points" << std::endl;
        // Add scoring logic here later
    }
};
