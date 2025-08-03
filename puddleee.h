 #pragma once
#include "Obstacle.h"

class Puddle : public Obstacle {
public:
    Puddle(float x, float y) {
        if (setTexture("assets/puddle.png")) {
            scaleToSize(64.0f, 32.0f); // wide and flat
        }
        setPosition(x, y); // set manually
    }
};
