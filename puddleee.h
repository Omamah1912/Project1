#pragma once
#include "Obstacle.h"

class Puddle : public Obstacle {
public:
    Puddle(float x, float y) {
        setTex("assets/puddle.png");
        setPosition(x, y);
    }
};
