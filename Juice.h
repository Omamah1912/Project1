#pragma once
#include "Collectible.h"

class Juice : public Collectible {
public:
    Juice(float x, float y) {
        setTex("assets/juice.png");
        setPosition(x, y);
    }

    void onCollect(Duck& duck) override {
        // Boost jump logic (to be implemented in Duck class)
    }
};
