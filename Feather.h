#pragma once
#include "Collectible.h"

class Feather : public Collectible {
public:
    Feather(float x, float y) {
        setTex("assets/feather.png");
        setScale(0.4f);  // Make feather smaller and more proportional
        setPosition(x, y);
    }

    void onCollect(Duck& duck) override {
        // Boost jump logic (to be implemented in Duck class)
    }
};
