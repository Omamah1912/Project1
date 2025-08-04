 #pragma once
#include "Obstacle.h"

class Puddle : public Obstacle {
public:
    Puddle(float x, float y) {
        if (setTexture("assets/puddle.png")) {
            scaleToSize(64.0f, 32.0f); 
        }
        setPosition(x, y); 
    }
};
