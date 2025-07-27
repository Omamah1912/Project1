#pragma once
#include "Obstacle.h"

class Puddle : public Obstacle {
public:
    Puddle(float x, float y) {
        setTex("assets/puddle.png");
        setScale(0.6f);  // Make puddle smaller and more proportional
        setPosition(x, y);
    }
};
