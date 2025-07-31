#pragma once
#include "Collectible.h"
#include "Duck.h"

class Key : public Collectible {
public:
    Key(float x, float y) {
        if (setTexture("assets/key.png")) {
            scaleToSize(40.0f, 40.0f); // 40x40 pixels
        }
        setPosition(x, y);
    }

    void onCollect(Duck& duck) override {
        std::cout << "Collected Juice! Speed boost!" << std::endl;
        // Add speed boost logic here later
    }
};