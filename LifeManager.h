#pragma once
#pragma once
#include <iostream>

class LifeManager {
public:
    int lives = 3;
    float invincibleTimer = 0.0f;
    float invincibleDuration = 1.5f; // seconds

    void update(float dt) {
        if (invincibleTimer > 0) {
            invincibleTimer -= dt;
        }
    }

    void reduceLife() {
        if (invincibleTimer <= 0) {
            lives--;
            invincibleTimer = invincibleDuration;

            std::cout << "Duck hit! Lives left: " << lives << "\n";

            if (lives <= 0) {
                std::cout << "Game Over!\n";
                exit(0); // End the game
            }
        }
    }
};

// Make a global life manager for now
inline LifeManager gLifeManager;

inline void reduceLife() {
    gLifeManager.reduceLife();
}
