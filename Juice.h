#pragma once
#include "Collectible.h"

class Juice : public Collectible {
public:
    Juice(float x, float y) {
        setTex("assets/juice.png");
        setScale(0.4f);  // Make juice smaller and more proportional
        setPosition(x, y);
    }

    void onCollect(Duck& duck) override {
        // Boost jump logic (to be implemented in Duck class)
    }
};
