
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Graphics/Shape.hpp>
#include "Entity.h"
#pragma once
using namespace std;
// ========== DUCK CLASS ========== //
class Duck: public Entity {
private:
    float speed = 200.0f;  
    float velocityX = 0.0f;
    float velocityY = 0.0f;
    bool down = true;

public:
    Duck() {
        setTex("assets/duck_brown.png");
        
        // Make duck large and easily visible
        setScale(2.0f);  // 2x original size
        
        // Start at a safe, visible position
        setPosition(400.f, 400.f);  // Near screen center, above ground
        
        std::cout << "Duck created at position: (400, 400) with scale 2.0" << std::endl;
    }


    void update(float dt) override {
        Jump(dt);
        Gravity(dt);
        Movement(dt);
        std::cout << "Duck pos: (" << position.x << ", " << position.y << ")\n";

        sprite.setPosition(position);

    }

    // Draw duck on the screen
    void render(sf::RenderWindow& window) override {
        window.draw(sprite);
    }

    void Gravity(float dt) {
        if (position.y >= groundLevel) {
            position.y = groundLevel;
            velocityY = 0;
        }
        else {
            velocityY += gravity * dt;
            position.y += velocityY * dt;
            down = true;
        }
        if (position.y < 0) {
            position.y = 0;
            velocityY = 0;
        }

    }


    void Movement(float dt) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            position.x -= speed * dt;
            std::cout << "Moving Left\n";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            position.x += speed * dt;
            std::cout << "Moving Right\n";
        }
    }


    void Jump(float dt) {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            velocityY = -500.0f;
            position.y += velocityY * dt;
            down = false;
            cout << "Moving up" << endl; 
            


        }
    }
    bool checkCollision(Entity* other) {
        return this->getBounds().intersects(other->getBounds()); // later on loop through all of the obstacles & check collsion and do whatever is required next
    }
    // for tornado collison//
    void applyImpulse(float dx, float dy) {
        position.x += dx;
        position.y += dy;
    }
    void enableSpeedBoost();
    void enableDoubleJump();




};

