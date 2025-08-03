#pragma once
#include "Collectible.h"
#include "Duck.h"

class Key : public Collectible {
public:
    Key(float x, float y) {
        if (setTexture("assets/key.png")) {
            scaleToSize(48.0f, 48.0f);// 40x40 pixels
        }
        setPosition(x, y);
    }

    void onCollect(Duck& duck) override {
        duck.addScore(30);
    }
};