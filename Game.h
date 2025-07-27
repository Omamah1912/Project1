

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
    sf::RectangleShape ground;
    Obstacle* obstacles[50];
    int obstacleCount;
    Collectible* collectibles[50];
    int collectibleCount;
    Enemy* enemies[10];
    int enemyCount;
    WorldLoader load;
    Tile* tiles[3000];  
    int tileCount = 0;
    sf::View camera;    

public:
    Game() : window(sf::VideoMode(800, 600), "Duck Dash") {
        std::cout << "=== Game Constructor Started ===" << std::endl;
        window.setFramerateLimit(60);

        // Initialize camera
        camera.setSize(800.f, 600.f);          
        camera.setCenter(400.f, 300.f);  // Start at screen center
        window.setView(camera);

        // Initialize arrays
        for (int i = 0; i < 3000; i++) tiles[i] = nullptr;
        for (int i = 0; i < 50; i++) obstacles[i] = nullptr;
        for (int i = 0; i < 50; i++) collectibles[i] = nullptr;
        for (int i = 0; i < 10; i++) enemies[i] = nullptr;

        obstacleCount = 0;
        collectibleCount = 0;
        enemyCount = 0;
        tileCount = 0;

        std::cout << "Arrays initialized, calling LoadWorldFromFile..." << std::endl;

        load.LoadWorldFromFile(
            "assets/temp.txt",
            tiles, tileCount,
            obstacles, obstacleCount,
            collectibles, collectibleCount,
            enemies, enemyCount
        );

        std::cout << "=== LoadWorldFromFile completed ===" << std::endl;
        std::cout << "Final counts - Tiles: " << tileCount
            << ", Obstacles: " << obstacleCount
            << ", Collectibles: " << collectibleCount
            << ", Enemies: " << enemyCount << std::endl;
    }

    void run() {
        std::cout << "=== Starting main game loop ===" << std::endl;

        while (window.isOpen()) {
            float dt = clock.restart().asSeconds();

            // Cap delta time to prevent huge jumps
            if (dt > 1.0f / 30.0f) dt = 1.0f / 60.0f;

            handleInput();
            update(dt);
            render();
        }
        std::cout << "=== Game loop ended ===" << std::endl;
    }

    ~Game() {
        std::cout << "=== Game Destructor Started ===" << std::endl;

        // Clean obstacles
        for (int i = 0; i < obstacleCount && i < 50; ++i) {
            if (obstacles[i]) {
                delete obstacles[i];
                obstacles[i] = nullptr;
            }
        }

        // Clean collectibles
        for (int i = 0; i < collectibleCount && i < 50; ++i) {
            if (collectibles[i]) {
                delete collectibles[i];
                collectibles[i] = nullptr;
            }
        }

        // Clean enemies
        for (int i = 0; i < enemyCount && i < 10; ++i) {
            if (enemies[i]) {
                delete enemies[i];
                enemies[i] = nullptr;
            }
        }

        // Clean tiles
        for (int i = 0; i < tileCount && i < 3000; ++i) {
            if (tiles[i]) {
                delete tiles[i];
                tiles[i] = nullptr;
            }
        }

        std::cout << "=== Game Destructor Completed ===" << std::endl;
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

        // Get duck position for camera
        sf::Vector2f duckPos = player.getPosition();
        std::cout << "Duck position: (" << duckPos.x << ", " << duckPos.y << ")" << std::endl;

        // Simple camera following - center on duck with slight offset
        sf::Vector2f targetCenter = sf::Vector2f(duckPos.x, duckPos.y - 50.f); // Duck slightly below center

        // Smooth camera movement
        sf::Vector2f currentCenter = camera.getCenter();
        sf::Vector2f newCenter = currentCenter + (targetCenter - currentCenter) * 5.0f * dt;

        // Very permissive camera bounds
        float minX = 200.f;
        float maxX = 6000.f;
        float minY = 100.f;
        float maxY = 1000.f;

        // Clamp camera
        if (newCenter.x < minX) newCenter.x = minX;
        if (newCenter.x > maxX) newCenter.x = maxX;
        if (newCenter.y < minY) newCenter.y = minY;
        if (newCenter.y > maxY) newCenter.y = maxY;

        camera.setCenter(newCenter);
        window.setView(camera);

        handleCollisions();
    }

    void render() {
        window.clear(sf::Color(135, 206, 235)); // Sky blue background

        // Get camera bounds for culling
        sf::Vector2f cameraCenter = camera.getCenter();
        float left = cameraCenter.x - 450.f;
        float right = cameraCenter.x + 450.f;
        float top = cameraCenter.y - 350.f;
        float bottom = cameraCenter.y + 350.f;

        // Render tiles with culling
        for (int i = 0; i < tileCount && i < 3000; ++i) {
            if (tiles[i]) {
                sf::Vector2f tilePos = tiles[i]->getPosition();
                if (tilePos.x >= left - 64 && tilePos.x <= right + 64 &&
                    tilePos.y >= top - 64 && tilePos.y <= bottom + 64) {
                    tiles[i]->render(window);
                }
            }
        }

        // Render obstacles with culling
        for (int i = 0; i < obstacleCount && i < 50; ++i) {
            if (obstacles[i]) {
                sf::Vector2f pos = obstacles[i]->getPosition();
                if (pos.x >= left - 64 && pos.x <= right + 64 &&
                    pos.y >= top - 64 && pos.y <= bottom + 64) {
                    obstacles[i]->render(window);
                }
            }
        }

        // Render collectibles with culling
        for (int i = 0; i < collectibleCount && i < 50; ++i) {
            if (collectibles[i]) {
                sf::Vector2f pos = collectibles[i]->getPosition();
                if (pos.x >= left - 64 && pos.x <= right + 64 &&
                    pos.y >= top - 64 && pos.y <= bottom + 64) {
                    collectibles[i]->render(window);
                }
            }
        }

        // Render enemies with culling
        for (int i = 0; i < enemyCount && i < 10; ++i) {
            if (enemies[i]) {
                sf::Vector2f pos = enemies[i]->getPosition();
                if (pos.x >= left - 64 && pos.x <= right + 64 &&
                    pos.y >= top - 64 && pos.y <= bottom + 64) {
                    enemies[i]->render(window);
                }
            }
        }

        // Always render the player (duck) - this is the most important part!
        sf::Vector2f duckPos = player.getPosition();
        std::cout << "Rendering duck at: (" << duckPos.x << ", " << duckPos.y << ")" << std::endl;
        player.render(window);

        // Draw a debug circle at duck position to help visualize
        sf::CircleShape debugCircle(20);
        debugCircle.setFillColor(sf::Color::Red);
        debugCircle.setPosition(duckPos.x - 10, duckPos.y - 10);
        window.draw(debugCircle);

        window.display();
    }

    void handleCollisions() {
        sf::FloatRect duckBounds = player.getBounds();

        for (int i = 0; i < obstacleCount; ++i) {
            if (obstacles[i] && duckBounds.intersects(obstacles[i]->getBounds())) {
                // Handle obstacle collisions
                std::cout << "Duck hit obstacle!" << std::endl;
            }
        }

        for (int i = 0; i < collectibleCount; ++i) {
            if (collectibles[i] && duckBounds.intersects(collectibles[i]->getBounds())) {
                collectibles[i]->onCollect(player);
                std::cout << "Duck collected item!" << std::endl;
                delete collectibles[i];
                collectibles[i] = nullptr;
            }
        }

        for (int i = 0; i < enemyCount; ++i) {
            if (enemies[i] && duckBounds.intersects(enemies[i]->getBounds())) {
                // Handle enemy collisions
                std::cout << "Duck hit enemy!" << std::endl;
            }
        }
    }
};