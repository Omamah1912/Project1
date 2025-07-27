

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include"Duck.h"
#include"Obstacle.h"
#include"Collectible.h"
#include"Bear.h"
#include"Tornado.h"
#include"WorldLoader.h"

class Game {
private:
    sf::RenderWindow window;
    Duck player;
    sf::Clock clock;

public:
    Game() : window(sf::VideoMode(800, 600), "Duck Dash") {
        std::cout << "=== Game Constructor Started ===" << std::endl;
        window.setFramerateLimit(60);
        
        // NO CAMERA - use default view
        std::cout << "=== Game Constructor Completed ===" << std::endl;
    }

    void run() {
        std::cout << "=== Starting main game loop ===" << std::endl;

        while (window.isOpen()) {
            float dt = clock.restart().asSeconds();
            if (dt > 1.0f / 30.0f) dt = 1.0f / 60.0f;

            handleInput();
            update(dt);
            render();
        }
        std::cout << "=== Game loop ended ===" << std::endl;
    }

private:
    void handleInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    void update(float dt) {
        player.update(dt);
        
        // Keep duck on screen
        sf::Vector2f duckPos = player.getPosition();
        std::cout << "Duck position: (" << duckPos.x << ", " << duckPos.y << ")" << std::endl;
        
        // Keep duck within screen bounds
        if (duckPos.x < 0) player.setPosition(0, duckPos.y);
        if (duckPos.x > 800) player.setPosition(800, duckPos.y);
        if (duckPos.y < 0) player.setPosition(duckPos.x, 0);
        if (duckPos.y > 600) player.setPosition(duckPos.x, 600);
    }

    void render() {
        // Clear with sky blue
        window.clear(sf::Color(135, 206, 235));

        // Draw ground line
        sf::RectangleShape ground(sf::Vector2f(800, 20));
        ground.setFillColor(sf::Color::Green);
        ground.setPosition(0, 450);  // Ground at Y=450
        window.draw(ground);

        // Get duck position
        sf::Vector2f duckPos = player.getPosition();
        std::cout << "Rendering duck at: (" << duckPos.x << ", " << duckPos.y << ")" << std::endl;
        
        // Draw duck
        player.render(window);

        // Draw big red circle at duck position for debugging
        sf::CircleShape debugCircle(40);
        debugCircle.setFillColor(sf::Color(255, 0, 0, 128)); // Semi-transparent red
        debugCircle.setPosition(duckPos.x - 20, duckPos.y - 20);
        window.draw(debugCircle);

        // Draw text showing duck position
        sf::Font font;
        // We'll skip font loading for now to avoid complications
        
        window.display();
    }
};