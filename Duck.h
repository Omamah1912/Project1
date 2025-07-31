#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Duck;

class Duck : public Entity {
private:
    float speed = 250.0f;
    float jumpSpeed = 400.0f;
    float velocityX = 0.0f;
    float velocityY = 0.0f;
    float gravity = 1200.0f;
    bool onGround = false;
    bool canJump = true;

public:
    Duck() {
        // Load duck texture and set size to 48x48 pixels
        if (setTexture("assets/duck_brown.png")) {
            scaleToSize(48.0f, 48.0f);
        }
        setPosition(64.0f, 500.0f); // Start position
    }

    void update(float dt) override {
        handleInput(dt);
        applyGravity(dt);
        updatePosition(dt);

        // Reset ground status (will be set by collision detection)
        onGround = false;
    }

    void render(sf::RenderWindow& window) override {
        window.draw(sprite);
    }

    // Called by Game class when duck collides with solid tile
    void setOnGround(bool grounded, float groundY = 0.0f) {
        if (grounded && velocityY >= 0) {
            onGround = true;
            canJump = true;
            velocityY = 0;
            position.y = groundY - getBounds().height;
            sprite.setPosition(position);
        }
    }

    // Apply impulse for tornado collision
    void applyImpulse(float dx, float dy) {
        velocityX += dx;
        velocityY += dy;
    }

    float getVelocityY() const { return velocityY; }
    bool isOnGround() const { return onGround; }

private:
    void handleInput(float dt) {
        // Horizontal movement
        velocityX = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velocityX = -speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velocityX = speed;
        }

        // Jumping
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

        // Prevent duck from going off screen boundaries
        if (position.x < 0) position.x = 0;
        if (position.y < 0) {
            position.y = 0;
            velocityY = 0;
        }

        sprite.setPosition(position);
    }
};