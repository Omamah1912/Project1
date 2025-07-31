#pragma once
#include "Collectible.h"
#include "Duck.h"

class Juice : public Collectible {
public:
    Juice(float x, float y) {
        if (setTexture("assets/juice.png")) {
            scaleToSize(40.0f, 40.0f); // 40x40 pixels
        }
        setPosition(x, y);
    }

    void onCollect(Duck& duck) override {
        std::cout << "Collected Juice! Speed boost!" << std::endl;
        // Add speed boost logic here later
    }
};