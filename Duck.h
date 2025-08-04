#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Collision.h"

class Duck : public Entity {
private:
    float speed = 250.0f;
    float jumpSpeed = 1000.0f;
    float velocityX = 0.0f;
    float velocityY = 0.0f;
    float gravity = 700.0f;
    bool onGround = false;
    bool canJump = true;
    int score = 0;
    int lives = 3;

    bool boosted = false;
    float timer = 0.0f;
    const float boost_dur = 10.0f;

    bool windShieldActive;
    bool inPuddle = false;
    sf::Vector2f spawnPosition;


public:
    Duck(sf::Vector2f spawn = sf::Vector2f(32.0f, 96.0f)) : spawnPosition(spawn) {
        if (setTexture("assets/duck_brown.png")) {
            scaleToSize(48.0f, 48.0f);
        }
        setPosition(spawnPosition.x, spawnPosition.y);
    }  

    void setSpawnPosition(const sf::Vector2f& spawn) {
        spawnPosition = spawn;
    }

    void update(float dt) override {
        handleInput(dt);
        applyGravity(dt);
        updateBoostTimer(dt);   
        updatePosition(dt);
        onGround = false;
    }

    void render(sf::RenderWindow& window) override {
        window.draw(sprite);
    }

    void addScore(int a) { score += a; }
    int getScore() const { return score; }

    void setOnGround(bool grounded, float groundY = 0.0f) {
        if (grounded && velocityY >= 0) {
            onGround = true;
            canJump = true;
            velocityY = 0;
            position.y = groundY - getBounds().height;
            sprite.setPosition(position);
        }
    }


    bool isOnGround() const { return onGround; }
    float getVelocityX() const { return velocityX; }
    float getVelocityY() const { return velocityY; }
    void setVelocityX(float vx) { velocityX = vx; }
    void setVelocityY(float vy) { velocityY = vy; }


    void applyJuiceBoost() {
        boosted = true;
        timer = boost_dur;

        speed *= 1.5f;
        jumpSpeed *= 1.2f;
        std::cout << "Speed Boosted!" << std::endl;
    }

    bool isBoosted() const { return boosted; }

    void setWindShield(bool active) { windShieldActive = active; }
    bool isWindShieldActive() const { return windShieldActive; }

    void applyImpulse(float impulseX, float impulseY) {
        if (!windShieldActive) {
            velocityX += impulseX;
            velocityY += impulseY;
        }
    }
    int getLives() const { return lives; }
    void loseLife() { if (lives > 0) lives--; }
    bool isDead() const { return lives <= 0; }

    sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }


    bool isInPuddle() const {
        return inPuddle;
    }

    void setInPuddle(bool state) {
        inPuddle = state;
    }

    void reset() {
        score = 0;
        lives = 3;
        boosted = false;
        windShieldActive = false;
        timer = 0.f;
        velocityX = velocityY = 0.f;

        speed = 250.f;
        jumpSpeed = 700.f;
        setPosition(spawnPosition.x, spawnPosition.y);
    }

private:
    void handleInput(float dt) {
        velocityX = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velocityX = -speed;
            sprite.setScale(-1.f, 1.f);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velocityX = speed;
            sprite.setScale(1.f, 1.f);
        }

        // Jump
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            && canJump && onGround) {
            velocityY = -jumpSpeed;
            onGround = false;
            canJump = false;
        }
    }

    void applyGravity(float dt) {
        if (!onGround) {
            velocityY += gravity * dt;
        }
    }

    void updatePosition(float dt) {
        position.x += velocityX * dt;
        position.y += velocityY * dt;

        if (position.x < 0) position.x = 0;
        if (position.y < 0) {
            position.y = 0;
            velocityY = 0;
        }

        sprite.setPosition(position);
    }


    void updateBoostTimer(float dt) {
        if (boosted) {
            timer -= dt;
            if (timer <= 0.0f) {
                boosted = false;

                speed = 250.0f;
                jumpSpeed = 1000.0f;
                std::cout << "Boost ended!" << std::endl;
            }
        }
       
    }
    

};
