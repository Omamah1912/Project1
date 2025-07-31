#pragma once
#include "Obstacle.h"

class Rock : public Obstacle {
public:
    Rock(float x, float y) {
        if (setTexture("assets/rock.png")) {
            scaleToSize(48.0f, 48.0f); // 48x48 pixels
        }
        setPosition(x, y);
    }
};