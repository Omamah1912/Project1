#pragma once
#include "Collectible.h"
#include "Duck.h"

class Juice : public Collectible {
private:
    bool collected = false;
public:
    Juice(float x, float y) {
        if (setTexture("assets/juice.png")) {
            scaleToSize(48.0f, 48.0f);// 40x40 pixels
        }
        setPosition(x, y);
    }

    void onCollect(Duck& duck) override {
        std::cout << "Collected Juice! Speed boost!" << std::endl;
        duck.applyJuiceBoost();
        collected = true;
    }
    bool isCollected() const {
        return collected;
    }
};