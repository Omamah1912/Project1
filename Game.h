

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
        camera.setCenter(400.f, 300.f);          
        window.setView(camera);


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

        // Update camera to follow the duck
        sf::Vector2f duckPos = player.getPosition();

        // Smooth camera following (
        sf::Vector2f currentCenter = camera.getCenter();
        sf::Vector2f targetCenter = sf::Vector2f(duckPos.x + 200.f, duckPos.y); // Offset duck slightly left of center

        // Smooth interpolation (adjust 5.0f for different smoothness)
        sf::Vector2f newCenter = currentCenter + (targetCenter - currentCenter) * 5.0f * dt;

        float cameraHalfWidth = 400.f;  
        float cameraHalfHeight = 300.f; 


        float worldLeft = cameraHalfWidth;          // Don't go past left edge
        float worldRight = 100 * 32 - cameraHalfWidth;  // 100 tiles * 32 pixels - half camera width
        float worldTop = cameraHalfHeight;          // Don't go past top
        float worldBottom = 20 * 32 - cameraHalfHeight; // 20 tiles * 32 pixels - half camera height

        // Clamp camera position
        if (newCenter.x < worldLeft) newCenter.x = worldLeft;
        if (newCenter.x > worldRight) newCenter.x = worldRight;
        if (newCenter.y < worldTop) newCenter.y = worldTop;
        if (newCenter.y > worldBottom) newCenter.y = worldBottom;

        camera.setCenter(newCenter);
        window.setView(camera);

        handleCollisions();
    }

    void render() {
        window.clear(sf::Color(135, 206, 235)); // Sky blue background instead of black

        // Get camera bounds for culling (only render what's visible)
        sf::Vector2f cameraCenter = camera.getCenter();
        float left = cameraCenter.x - 450.f;   // A bit more than half screen width for buffer
        float right = cameraCenter.x + 450.f;
        float top = cameraCenter.y - 350.f;    // A bit more than half screen height for buffer
        float bottom = cameraCenter.y + 350.f;

        // Render tiles with frustum culling
        int tilesRendered = 0;
        for (int i = 0; i < tileCount && i < 3000; ++i) {
            if (tiles[i]) {
                sf::Vector2f tilePos = tiles[i]->getPosition();
                // Only render tiles that are visible on screen (adjusted for 32-pixel tiles)
                if (tilePos.x >= left - 32 && tilePos.x <= right + 32 &&
                    tilePos.y >= top - 32 && tilePos.y <= bottom + 32) {
                    tiles[i]->render(window);
                    tilesRendered++;
                }
            }
        }

        // Render obstacles with culling
        for (int i = 0; i < obstacleCount && i < 50; ++i) {
            if (obstacles[i]) {
                sf::Vector2f pos = obstacles[i]->getPosition();
                if (pos.x >= left - 32 && pos.x <= right + 32 &&
                    pos.y >= top - 32 && pos.y <= bottom + 32) {
                    obstacles[i]->render(window);
                }
            }
        }

        // Render collectibles with culling
        for (int i = 0; i < collectibleCount && i < 50; ++i) {
            if (collectibles[i]) {
                sf::Vector2f pos = collectibles[i]->getPosition();
                if (pos.x >= left - 32 && pos.x <= right + 32 &&
                    pos.y >= top - 32 && pos.y <= bottom + 32) {
                    collectibles[i]->render(window);
                }
            }
        }

        // Render enemies with culling
        for (int i = 0; i < enemyCount && i < 10; ++i) {
            if (enemies[i]) {
                sf::Vector2f pos = enemies[i]->getPosition();
                if (pos.x >= left - 32 && pos.x <= right + 32 &&
                    pos.y >= top - 32 && pos.y <= bottom + 32) {
                    enemies[i]->render(window);
                }
            }
        }

        // Always render the player
        player.render(window);

        window.display();
    }

    void handleCollisions() {
        sf::FloatRect duckBounds = player.getBounds();

        for (int i = 0; i < obstacleCount; ++i) {
            if (obstacles[i] && duckBounds.intersects(obstacles[i]->getBounds())) {
                // Handle obstacle collisions
            }
        }

        for (int i = 0; i < collectibleCount; ++i) {
            if (collectibles[i] && duckBounds.intersects(collectibles[i]->getBounds())) {
                collectibles[i]->onCollect(player);
                delete collectibles[i];
                collectibles[i] = nullptr;
            }
        }

        for (int i = 0; i < enemyCount; ++i) {
            if (enemies[i] && duckBounds.intersects(enemies[i]->getBounds())) {
                // Handle enemy collisions
            }
        }
    }
};