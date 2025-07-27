#pragma once
#include "Obstacle.h"

class Rock : public Obstacle {
public:
    Rock(float x, float y) {
        setTex("assets/rock.png");
        setScale(0.5f);  // Make rock smaller and more proportional
        setPosition(x, y);
    }
};
