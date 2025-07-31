#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Duck.h"
#include "Obstacle.h"
#include "Collectible.h"
#include "Enemy.h"
#include "WorldLoader.h"

class Game {
private:
    sf::RenderWindow window;
    Duck player;
    sf::Clock clock;

    // Game objects arrays
    Tile* tiles[MAX_TILES];
    int tileCount;
    Obstacle* obstacles[MAX_OBSTACLES];
    int obstacleCount;
    Collectible* collectibles[MAX_COLLECTIBLES];
    int collectibleCount;
    Enemy* enemies[MAX_ENEMIES];
    int enemyCount;

    // Camera
    sf::View camera;
    float worldWidth;
    float worldHeight;

    WorldLoader loader;

public:
    Game() : window(sf::VideoMode(1024, 768), "Duck Dash - Fixed Version") {
        std::cout << "Initializing Duck Dash..." << std::endl;

        window.setFramerateLimit(60);

        // Initialize arrays to nullptr
        for (int i = 0; i < MAX_TILES; i++) tiles[i] = nullptr;
        for (int i = 0; i < MAX_OBSTACLES; i++) obstacles[i] = nullptr;
        for (int i = 0; i < MAX_COLLECTIBLES; i++) collectibles[i] = nullptr;
        for (int i = 0; i < MAX_ENEMIES; i++) enemies[i] = nullptr;

        // Reset counters
        tileCount = 0;
        obstacleCount = 0;
        collectibleCount = 0;
        enemyCount = 0;

        // Load world
        loader.LoadWorldFromFile(
            "assets/temp.txt",
            tiles, tileCount,
            obstacles, obstacleCount,
            collectibles, collectibleCount,
            enemies, enemyCount
        );

        // Calculate world dimensions
        calculateWorldBounds();

        // Position duck on first solid tile
        positionDuckOnGround();

        // Setup camera
        camera.setSize(1024.0f, 768.0f);
        camera.setCenter(player.getPosition().x, player.getPosition().y - 100.0f);
        window.setView(camera);

        std::cout << "Game initialized successfully!" << std::endl;
    }

    ~Game() {
        // Clean up memory
        for (int i = 0; i < tileCount; i++) {
            delete tiles[i];
        }
        for (int i = 0; i < obstacleCount; i++) {
            delete obstacles[i];
        }
        for (int i = 0; i < collectibleCount; i++) {
            delete collectibles[i];
        }
        for (int i = 0; i < enemyCount; i++) {
            delete enemies[i];
        }
    }

    void run() {
        while (window.isOpen()) {
            float dt = clock.restart().asSeconds();
            if (dt > 1.0f / 30.0f) dt = 1.0f / 60.0f; // Cap delta time

            handleEvents();
            update(dt);
            render();
        }
    }

private:
    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    void update(float dt) {
        player.update(dt);

        // Handle tile collisions (ground detection)
        handleTileCollisions();

        // Handle other collisions
        handleObstacleCollisions();
        handleCollectibleCollisions();
        handleEnemyCollisions();

        // Update camera to follow duck
        updateCamera();
    }

    void handleTileCollisions() {
        sf::FloatRect duckBounds = player.getBounds();
        sf::FloatRect nextFrameBounds = duckBounds;
        nextFrameBounds.top += player.getVelocityY() * (1.0f / 60.0f); // Predict next position

        float highestGround = worldHeight; // Start with world bottom
        bool foundGround = false;

        for (int i = 0; i < tileCount; i++) {
            if (tiles[i] && tiles[i]->isSolid()) {
                sf::FloatRect tileBounds = tiles[i]->getBounds();

                // Check if duck is above this tile horizontally
                if (duckBounds.left < tileBounds.left + tileBounds.width &&
                    duckBounds.left + duckBounds.width > tileBounds.left) {

                    // Check if duck is falling onto this tile
                    if (player.getVelocityY() >= 0 &&
                        duckBounds.top + duckBounds.height <= tileBounds.top + 10 &&
                        nextFrameBounds.top + nextFrameBounds.height >= tileBounds.top) {

                        if (tileBounds.top < highestGround) {
                            highestGround = tileBounds.top;
                            foundGround = true;
                        }
                    }
                }
            }
        }

        if (foundGround) {
            player.setOnGround(true, highestGround);
        }
    }

    void handleObstacleCollisions() {
        sf::FloatRect duckBounds = player.getBounds();

        for (int i = 0; i < obstacleCount; i++) {
            if (obstacles[i] && duckBounds.intersects(obstacles[i]->getBounds())) {
                // Special handling for tornado
                Tornado* tornado = dynamic_cast<Tornado*>(obstacles[i]);
                if (tornado) {
                    player.applyImpulse(-150.0f, -100.0f); // Push duck away
                }
                std::cout << "Duck hit obstacle!" << std::endl;
            }
        }
    }

    void handleCollectibleCollisions() {
        sf::FloatRect duckBounds = player.getBounds();

        for (int i = 0; i < collectibleCount; i++) {
            if (collectibles[i] && duckBounds.intersects(collectibles[i]->getBounds())) {
                collectibles[i]->onCollect(player);
                std::cout << "Duck collected item!" << std::endl;

                // Remove collected item
                delete collectibles[i];
                collectibles[i] = nullptr;
            }
        }
    }

    void handleEnemyCollisions() {
        sf::FloatRect duckBounds = player.getBounds();

        for (int i = 0; i < enemyCount; i++) {
            if (enemies[i] && duckBounds.intersects(enemies[i]->getBounds())) {
                enemies[i]->onCollide();
                std::cout << "Duck hit enemy!" << std::endl;
                // Could add damage or game over logic here
            }
        }
    }

    void updateCamera() {
        sf::Vector2f duckPos = player.getPosition();

        // Smooth camera following
        sf::Vector2f targetCenter = sf::Vector2f(duckPos.x, duckPos.y - 100.0f);
        sf::Vector2f currentCenter = camera.getCenter();

        // Lerp camera movement for smoothness
        sf::Vector2f newCenter = currentCenter + (targetCenter - currentCenter) * 3.0f * (1.0f / 60.0f);

        // Constrain camera to world bounds
        float halfWidth = camera.getSize().x / 2.0f;
        float halfHeight = camera.getSize().y / 2.0f;

        if (newCenter.x - halfWidth < 0) newCenter.x = halfWidth;
        if (newCenter.x + halfWidth > worldWidth) newCenter.x = worldWidth - halfWidth;
        if (newCenter.y - halfHeight < 0) newCenter.y = halfHeight;
        if (newCenter.y + halfHeight > worldHeight) newCenter.y = worldHeight - halfHeight;

        camera.setCenter(newCenter);
        window.setView(camera);
    }

    void render() {
        window.clear(sf::Color(135, 206, 235)); // Sky blue

        // Get camera bounds for culling
        sf::Vector2f cameraCenter = camera.getCenter();
        sf::Vector2f cameraSize = camera.getSize();
        float left = cameraCenter.x - cameraSize.x / 2.0f - 100.0f;
        float right = cameraCenter.x + cameraSize.x / 2.0f + 100.0f;
        float top = cameraCenter.y - cameraSize.y / 2.0f - 100.0f;
        float bottom = cameraCenter.y + cameraSize.y / 2.0f + 100.0f;

        // Render tiles
        for (int i = 0; i < tileCount; i++) {
            if (tiles[i]) {
                sf::Vector2f pos = tiles[i]->getPosition();
                if (pos.x >= left && pos.x <= right && pos.y >= top && pos.y <= bottom) {
                    tiles[i]->render(window);
                }
            }
        }

        // Render obstacles
        for (int i = 0; i < obstacleCount; i++) {
            if (obstacles[i]) {
                sf::Vector2f pos = obstacles[i]->getPosition();
                if (pos.x >= left && pos.x <= right && pos.y >= top && pos.y <= bottom) {
                    obstacles[i]->render(window);
                }
            }
        }

        // Render collectibles
        for (int i = 0; i < collectibleCount; i++) {
            if (collectibles[i]) {
                sf::Vector2f pos = collectibles[i]->getPosition();
                if (pos.x >= left && pos.x <= right && pos.y >= top && pos.y <= bottom) {
                    collectibles[i]->render(window);
                }
            }
        }

        // Render enemies
        for (int i = 0; i < enemyCount; i++) {
            if (enemies[i]) {
                sf::Vector2f pos = enemies[i]->getPosition();
                if (pos.x >= left && pos.x <= right && pos.y >= top && pos.y <= bottom) {
                    enemies[i]->render(window);
                }
            }
        }

        // Always render the duck
        player.render(window);

        window.display();
    }

    void calculateWorldBounds() {
        worldWidth = 0;
        worldHeight = 0;

        for (int i = 0; i < tileCount; i++) {
            if (tiles[i]) {
                sf::Vector2f pos = tiles[i]->getPosition();
                sf::FloatRect bounds = tiles[i]->getBounds();

                if (pos.x + bounds.width > worldWidth) {
                    worldWidth = pos.x + bounds.width;
                }
                if (pos.y + bounds.height > worldHeight) {
                    worldHeight = pos.y + bounds.height;
                }
            }
        }

        std::cout << "World bounds: " << worldWidth << "x" << worldHeight << std::endl;
    }

    void positionDuckOnGround() {
        // Find the first ground tile and position duck above it
        for (int i = 0; i < tileCount; i++) {
            if (tiles[i] && tiles[i]->getTextureName() == "assets/ground.png") {
                sf::Vector2f tilePos = tiles[i]->getPosition();
                player.setPosition(tilePos.x, tilePos.y - 48.0f); // Duck height = 48px
                std::cout << "Duck positioned at: " << tilePos.x << ", " << tilePos.y - 48.0f << std::endl;
                break;
            }
        }
    }
};