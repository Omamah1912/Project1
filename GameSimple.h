#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Duck.h"

class GameSimple {
private:
    sf::RenderWindow window;
    Duck player;
    sf::Clock clock;
    sf::View camera;

public:
    GameSimple() : window(sf::VideoMode(800, 600), "Duck Dash - Simple") {
        std::cout << "=== Simple Game Constructor Started ===" << std::endl;
        window.setFramerateLimit(60);

        // Initialize camera
        camera.setSize(800.f, 600.f);
        camera.setCenter(400.f, 300.f);
        window.setView(camera);

        std::cout << "=== Simple Game Constructor Completed ===" << std::endl;
    }

    void run() {
        std::cout << "=== Starting simple game loop ===" << std::endl;

        while (window.isOpen()) {
            float dt = clock.restart().asSeconds();

            // Cap delta time
            if (dt > 1.0f / 30.0f) dt = 1.0f / 60.0f;

            handleInput();
            update(dt);
            render();
        }
        std::cout << "=== Simple game loop ended ===" << std::endl;
    }

private:
    void handleInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                std::cout << "Window close event received" << std::endl;
                window.close();
            }
        }
    }

    void update(float dt) {
        player.update(dt);

        // Get duck position
        sf::Vector2f duckPos = player.getPosition();
        std::cout << "Duck position: (" << duckPos.x << ", " << duckPos.y << ")" << std::endl;

        // Simple camera following
        camera.setCenter(duckPos.x, duckPos.y - 50.f);
        window.setView(camera);
    }

    void render() {
        // Clear with sky blue
        window.clear(sf::Color(135, 206, 235));

        // Draw duck
        sf::Vector2f duckPos = player.getPosition();
        std::cout << "Rendering duck at: (" << duckPos.x << ", " << duckPos.y << ")" << std::endl;
        player.render(window);

        // Draw debug circle at duck position
        sf::CircleShape debugCircle(30);
        debugCircle.setFillColor(sf::Color::Red);
        debugCircle.setPosition(duckPos.x - 15, duckPos.y - 15);
        window.draw(debugCircle);

        // Draw ground line for reference
        sf::RectangleShape groundLine(sf::Vector2f(1600, 5));
        groundLine.setFillColor(sf::Color::Green);
        groundLine.setPosition(0, 550);
        window.draw(groundLine);

        window.display();
    }
};