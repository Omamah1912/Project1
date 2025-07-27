#pragma once
#include "Collectible.h"

class Seed : public Collectible {
public:
    Seed(float x, float y) {
        setTex("assets/seed.png");
        setScale(0.3f);  // Make seed smaller and more proportional
        setPosition(x, y);
    }

    void onCollect(Duck& duck) override {
        // Boost jump logic (to be implemented in Duck class)
    }
};
