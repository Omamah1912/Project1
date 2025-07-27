#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include"Duck.h"
#include"Obstacle.h"
#include"Collectible.h"
#include"Bear.h"
#include"Tornado.h"
#include"WorldLoader.h"

class GameFixed {
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

    // IMPORTANT: World scaling factors
    const float WORLD_SCALE = 0.3f;  // Scale down the massive world to fit screen
    const float SCREEN_GROUND_Y = 500.0f;  // Ground level in screen coordinates

public:
    GameFixed() : window(sf::VideoMode(800, 600), "Duck Dash - Fixed") {
        std::cout << "=== Game Constructor Started ===" << std::endl;
        window.setFramerateLimit(60);

        // Initialize camera to show game area
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

        std::cout << "Loading world with scaling factor: " << WORLD_SCALE << std::endl;

        load.LoadWorldFromFile(
            "assets/simple_map.txt",
            tiles, tileCount,
            obstacles, obstacleCount,
            collectibles, collectibleCount,
            enemies, enemyCount
        );

        // SCALE DOWN all world objects to fit our screen
        scaleWorldToScreen();

        std::cout << "=== LoadWorldFromFile completed ===" << std::endl;
        std::cout << "World scaled to fit screen. Ground level: " << SCREEN_GROUND_Y << std::endl;
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

    ~GameFixed() {
        // Cleanup (same as before)
        for (int i = 0; i < obstacleCount && i < 50; ++i) {
            if (obstacles[i]) {
                delete obstacles[i];
                obstacles[i] = nullptr;
            }
        }
        for (int i = 0; i < collectibleCount && i < 50; ++i) {
            if (collectibles[i]) {
                delete collectibles[i];
                collectibles[i] = nullptr;
            }
        }
        for (int i = 0; i < enemyCount && i < 10; ++i) {
            if (enemies[i]) {
                delete enemies[i];
                enemies[i] = nullptr;
            }
        }
        for (int i = 0; i < tileCount && i < 3000; ++i) {
            if (tiles[i]) {
                delete tiles[i];
                tiles[i] = nullptr;
            }
        }
    }

private:
    void scaleWorldToScreen() {
        std::cout << "Scaling world objects to screen coordinates..." << std::endl;
        
        // Scale and reposition all tiles
        for (int i = 0; i < tileCount && i < 3000; ++i) {
            if (tiles[i]) {
                sf::Vector2f oldPos = tiles[i]->getPosition();
                sf::Vector2f newPos = sf::Vector2f(
                    oldPos.x * WORLD_SCALE,
                    oldPos.y * WORLD_SCALE + 100.0f  // Offset to keep ground visible
                );
                tiles[i]->setPosition(newPos.x, newPos.y);
            }
        }

        // Scale obstacles
        for (int i = 0; i < obstacleCount && i < 50; ++i) {
            if (obstacles[i]) {
                sf::Vector2f oldPos = obstacles[i]->getPosition();
                sf::Vector2f newPos = sf::Vector2f(
                    oldPos.x * WORLD_SCALE,
                    oldPos.y * WORLD_SCALE + 100.0f
                );
                obstacles[i]->setPosition(newPos.x, newPos.y);
            }
        }

        // Scale collectibles
        for (int i = 0; i < collectibleCount && i < 50; ++i) {
            if (collectibles[i]) {
                sf::Vector2f oldPos = collectibles[i]->getPosition();
                sf::Vector2f newPos = sf::Vector2f(
                    oldPos.x * WORLD_SCALE,
                    oldPos.y * WORLD_SCALE + 100.0f
                );
                collectibles[i]->setPosition(newPos.x, newPos.y);
            }
        }

        // Scale enemies
        for (int i = 0; i < enemyCount && i < 10; ++i) {
            if (enemies[i]) {
                sf::Vector2f oldPos = enemies[i]->getPosition();
                sf::Vector2f newPos = sf::Vector2f(
                    oldPos.x * WORLD_SCALE,
                    oldPos.y * WORLD_SCALE + 100.0f
                );
                enemies[i]->setPosition(newPos.x, newPos.y);
            }
        }

        std::cout << "World scaling completed!" << std::endl;
    }

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

        // Get duck position
        sf::Vector2f duckPos = player.getPosition();
        std::cout << "Duck position: (" << duckPos.x << ", " << duckPos.y << ")" << std::endl;

        // Simple camera following - keep duck centered
        camera.setCenter(duckPos.x, duckPos.y - 100.f);
        window.setView(camera);

        handleCollisions();
    }

    void render() {
        window.clear(sf::Color(135, 206, 235)); // Sky blue

        // Get camera bounds for culling
        sf::Vector2f cameraCenter = camera.getCenter();
        float left = cameraCenter.x - 450.f;
        float right = cameraCenter.x + 450.f;
        float top = cameraCenter.y - 350.f;
        float bottom = cameraCenter.y + 350.f;

        // Render tiles (now properly scaled)
        for (int i = 0; i < tileCount && i < 3000; ++i) {
            if (tiles[i]) {
                sf::Vector2f tilePos = tiles[i]->getPosition();
                if (tilePos.x >= left - 64 && tilePos.x <= right + 64 &&
                    tilePos.y >= top - 64 && tilePos.y <= bottom + 64) {
                    tiles[i]->render(window);
                }
            }
        }

        // Render obstacles
        for (int i = 0; i < obstacleCount && i < 50; ++i) {
            if (obstacles[i]) {
                sf::Vector2f pos = obstacles[i]->getPosition();
                if (pos.x >= left - 64 && pos.x <= right + 64 &&
                    pos.y >= top - 64 && pos.y <= bottom + 64) {
                    obstacles[i]->render(window);
                }
            }
        }

        // Render collectibles
        for (int i = 0; i < collectibleCount && i < 50; ++i) {
            if (collectibles[i]) {
                sf::Vector2f pos = collectibles[i]->getPosition();
                if (pos.x >= left - 64 && pos.x <= right + 64 &&
                    pos.y >= top - 64 && pos.y <= bottom + 64) {
                    collectibles[i]->render(window);
                }
            }
        }

        // Render enemies
        for (int i = 0; i < enemyCount && i < 10; ++i) {
            if (enemies[i]) {
                sf::Vector2f pos = enemies[i]->getPosition();
                if (pos.x >= left - 64 && pos.x <= right + 64 &&
                    pos.y >= top - 64 && pos.y <= bottom + 64) {
                    enemies[i]->render(window);
                }
            }
        }

        // Always render the duck
        sf::Vector2f duckPos = player.getPosition();
        player.render(window);

        // Debug circle
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
                std::cout << "Duck hit enemy!" << std::endl;
            }
        }
    }
};