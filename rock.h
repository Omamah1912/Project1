#pragma once
#include "Obstacle.h"

class Rock : public Obstacle {
public:
    Rock(float x, float y) {
        setTex("assets/rock.png");
        setPosition(x, y);
    }
};
