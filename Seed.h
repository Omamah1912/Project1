#pragma once
#include "Collectible.h"

class Seed : public Collectible {
public:
    Seed(float x, float y) {
        setTex("assets/seed.png");
        setPosition(x, y);
    }

    void onCollect(Duck& duck) override {
        // Boost jump logic (to be implemented in Duck class)
    }
};
