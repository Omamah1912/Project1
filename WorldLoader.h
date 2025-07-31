#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "Tile.h"
#include "Obstacle.h" 
#include "Collectible.h"
#include "Bear.h"
#include "Tornado.h"
#include "Feather.h"
#include "Seed.h"
#include "Juice.h"
#include "rock.h"
#include "puddleee.h"

const int MAX_TILES = 3000;
const int MAX_OBSTACLES = 100;
const int MAX_COLLECTIBLES = 100;
const int MAX_ENEMIES = 50;
const int TILE_SIZE = 64;

class WorldLoader {
public:
    static void LoadWorldFromFile(
        const std::string& filename,
        Tile* tiles[], int& tileCount,
        Obstacle* obstacles[], int& obstacleCount,
        Collectible* collectibles[], int& collectibleCount,
        Enemy* enemies[], int& enemyCount)
    {
        std::cout << "Loading world from: " << filename << std::endl;

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "ERROR: Cannot open map file: " << filename << std::endl;
            return;
        }

        // Reset counters
        tileCount = 0;
        obstacleCount = 0;
        collectibleCount = 0;
        enemyCount = 0;

        std::string line;
        int row = 0;

        while (std::getline(file, line) && row < 25) {
            for (size_t col = 0; col < line.length() && col < 150; ++col) {
                char ch = line[col];
                float x = static_cast<float>(col * TILE_SIZE);
                float y = static_cast<float>(row * TILE_SIZE);

                switch (ch) {
                case '#': // Ground tile
                    if (tileCount < MAX_TILES) {
                        tiles[tileCount] = new Tile("assets/grass.png", x, y);
                        if (tiles[tileCount]->isValid()) {
                            tileCount++;
                        }
                        else {
                            delete tiles[tileCount];
                        }
                    }
                    break;

                case 'G': // Grass tile
                    if (tileCount < MAX_TILES) {
                        tiles[tileCount] = new Tile("assets/ground.png", x, y);
                        if (tiles[tileCount]->isValid()) {
                            tileCount++;
                        }
                        else {
                            delete tiles[tileCount];
                        }
                    }
                    break;

                case 'B': // Bear enemy
                    if (enemyCount < MAX_ENEMIES) {
                        enemies[enemyCount] = new Bear(x, y);
                        enemyCount++;
                    }
                    break;

                case 'T': // Tornado
                    if (obstacleCount < MAX_OBSTACLES) {
                        obstacles[obstacleCount] = new Tornado(x, y);
                        obstacleCount++;
                    }
                    break;

                case 'R': // Rock
                    if (obstacleCount < MAX_OBSTACLES) {
                        obstacles[obstacleCount] = new Rock(x, y);
                        obstacleCount++;
                    }
                    break;

                case 'P': // Puddle
                    if (obstacleCount < MAX_OBSTACLES) {
                        obstacles[obstacleCount] = new Puddle(x, y);
                        obstacleCount++;
                    }
                    break;

                case 'F': // Feather
                    if (collectibleCount < MAX_COLLECTIBLES) {
                        collectibles[collectibleCount] = new Feather(x, y);
                        collectibleCount++;
                    }
                    break;

                case 'S': // Seed
                    if (collectibleCount < MAX_COLLECTIBLES) {
                        collectibles[collectibleCount] = new Seed(x, y);
                        collectibleCount++;
                    }
                    break;

                case 'J': // Juice
                    if (collectibleCount < MAX_COLLECTIBLES) {
                        collectibles[collectibleCount] = new Juice(x, y);
                        collectibleCount++;
                    }
                    break;

                default:
                    // Skip empty spaces and unknown characters
                    break;
                }
            }
            row++;
        }

        file.close();

        std::cout << "World loaded successfully!" << std::endl;
        std::cout << "Tiles: " << tileCount << std::endl;
        std::cout << "Obstacles: " << obstacleCount << std::endl;
        std::cout << "Collectibles: " << collectibleCount << std::endl;
        std::cout << "Enemies: " << enemyCount << std::endl;
    }
};