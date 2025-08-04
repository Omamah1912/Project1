#pragma once
#include "Enemy.h"
#include <SFML/System.hpp>
#include <cmath>

#include"LifeManager.h"
class Bear : public Enemy {
private:
    enum State { PATROLLING, CHASING, STUNNED } state = PATROLLING;
    float speed = 50.0f;
    float chaseSpeed = 120.0f;
    float detectionRadius = 300.0f;
    float stunTime = 0.0f;
    int chaseCount = 0;                 // How many chases so far
    int maxChases = 3;                  // Limit to 3
    bool hasHitDuckThisChase = false;   // Prevent multiple life losses per chase

    sf::Vector2f duckPosCache;
    bool duckInPuddleCache = false;

public:
    Bear(float x, float y) {
        if (setTexture("assets/bear.png")) {
            scaleToSize(80.0f, 80.0f);
        }
        setPosition(x, y);
    }

    void update(float dt) override {
        runAI(dt, duckPosCache, duckInPuddleCache);
    }

    void setDuckInfo(const sf::Vector2f& duckPos, bool duckInPuddle) {
        duckPosCache = duckPos;
        duckInPuddleCache = duckInPuddle;
    }

    void onCollide() override {
        if (!hasHitDuckThisChase && chaseCount <= maxChases) {
            gLifeManager.reduceLife(); 
            hasHitDuckThisChase = true;
            state = STUNNED;
            stunTime = 2.0f;
        }
    }
    bool isChasing() const {
        return state == CHASING;
    }

private:
    void runAI(float dt, const sf::Vector2f& duckPos, bool duckInPuddle) {
        if (stunTime > 0) {
            stunTime -= dt;
            if (stunTime <= 0) {
                state = PATROLLING;
            }
            return;
        }

        float dx = duckPos.x - getPosition().x;
        float dy = duckPos.y - getPosition().y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (state == PATROLLING) {
            if (dist < detectionRadius && chaseCount < maxChases) {
                state = CHASING;
                chaseCount++;
                hasHitDuckThisChase = false; 
            }
        }

        if (state == CHASING) {
 
            if (dist > detectionRadius * 1.5f) { 
                state = PATROLLING;
                return;
            }

            if (duckInPuddle) {
                state = STUNNED;
                stunTime = 2.0f;
                return;
            }

            float moveX = (dx / dist) * chaseSpeed * dt;
            float moveY = (dy / dist) * chaseSpeed * dt;
            setPosition(getPosition().x + moveX, getPosition().y + moveY);
        }

    }
};
