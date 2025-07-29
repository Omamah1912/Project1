

#pragma once
using namespace std;
#include<istream>
#include<ostream>
#include <fstream>
#include <string>
#include <iostream>
#include "Tile.h"
#include "Obstacle.h"
#include "Collectible.h"
#include "Bear.h"
#include "puddleee.h"
#include "Tornado.h"
#include "Rock.h"
#include "Feather.h"
#include "Juice.h"
#include "Seed.h"

const int MAX_TILES = 3000;      
const int MAX_OBSTACLES = 100;
const int MAX_COLLECTIBLES = 100;
const int MAX_ENEMIES = 50;
const int TILE_SIZE = 32; // Reduced from 64 to 32 for better proportions

class WorldLoader {
public:
    static void LoadWorldFromFile(
        const string& filename,
        Tile* tiles[], int& tileCount,
        Obstacle* obstacles[], int& obstacleCount,
        Collectible* collectibles[], int& collectibleCount,
        Enemy* enemies[], int& enemyCount)
    {
        std::cout << "=== LoadWorldFromFile Started ===" << std::endl;
        std::cout << "Trying to open: " << filename << std::endl;

        ifstream file(filename);

        if (!file.is_open()) {
            std::cout << "ERROR: Failed to open map file: " << filename << std::endl;
            tileCount = 0;
            obstacleCount = 0;
            collectibleCount = 0;
            enemyCount = 0;
            return;
        }

        std::cout << "File opened successfully!" << std::endl;

        string line;
        int row = 0;

        // Reset all counts
        tileCount = 0;
        obstacleCount = 0;
        collectibleCount = 0;
        enemyCount = 0;

        while (getline(file, line) && row < 25) { // Safety limit on rows
            std::cout << "Row " << row << ": length=" << line.length() << std::endl;

            // Process each character in the line
            for (size_t col = 0; col < line.length() && col < 150; ++col) { // Safety limit on columns
                char ch = line[col];
                float x = static_cast<float>(col * TILE_SIZE);
                float y = static_cast<float>(row * TILE_SIZE);

                // Show progress every 50 tiles
                if ((tileCount + obstacleCount + collectibleCount + enemyCount) % 50 == 0) {
                    std::cout << "Progress: " << (tileCount + obstacleCount + collectibleCount + enemyCount) << " objects created..." << std::endl;
                }

                try {
                    switch (ch) {
                    case '#':
                        if (tileCount < MAX_TILES - 1) {
                            tiles[tileCount] = new Tile("assets/ground.png", x, y);
                            if (tiles[tileCount] != nullptr) {
                                tileCount++;
                            }
                            else {
                                std::cout << "ERROR: Failed to create ground tile at (" << x << "," << y << ")" << std::endl;
                            }
                        }
                        else {
                            std::cout << "WARNING: Max tiles reached (" << MAX_TILES << "), skipping ground tile" << std::endl;
                        }
                        break;

                    case 'G':
                        if (tileCount < MAX_TILES - 1) {
                            tiles[tileCount] = new Tile("assets/grass.png", x, y);
                            if (tiles[tileCount] != nullptr) {
                                tileCount++;
                            }
                        }
                        break;

                    case 'C':
                        if (tileCount < MAX_TILES - 1) {
                            tiles[tileCount] = new Tile("assets/checkpoint.png", x, y);
                            if (tiles[tileCount] != nullptr) {
                                tileCount++;
                            }
                        }
                        break;

                    case 'R':
                        if (obstacleCount < MAX_OBSTACLES - 1) {
                            obstacles[obstacleCount] = new Rock(x, y);
                            if (obstacles[obstacleCount] != nullptr) {
                                obstacleCount++;
                            }
                        }
                        break;

                    case 'P':
                        if (obstacleCount < MAX_OBSTACLES - 1) {
                            obstacles[obstacleCount] = new Puddle(x, y);
                            if (obstacles[obstacleCount] != nullptr) {
                                obstacleCount++;
                            }
                        }
                        break;

                    case 'T':
                        if (obstacleCount < MAX_OBSTACLES - 1) {
                            obstacles[obstacleCount] = new Tornado(x, y);
                            if (obstacles[obstacleCount] != nullptr) {
                                obstacleCount++;
                            }
                        }
                        break;

                    case 'B':
                        if (enemyCount < MAX_ENEMIES - 1) {
                            enemies[enemyCount] = new Bear(x, y);
                            if (enemies[enemyCount] != nullptr) {
                                enemyCount++;
                            }
                        }
                        break;

                    case 'F':
                        if (collectibleCount < MAX_COLLECTIBLES - 1) {
                            collectibles[collectibleCount] = new Feather(x, y);
                            if (collectibles[collectibleCount] != nullptr) {
                                collectibleCount++;
                            }
                        }
                        break;

                    case 'J':
                        if (collectibleCount < MAX_COLLECTIBLES - 1) {
                            collectibles[collectibleCount] = new Juice(x, y);
                            if (collectibles[collectibleCount] != nullptr) {
                                collectibleCount++;
                            }
                        }
                        break;

                    case 'S':
                        if (collectibleCount < MAX_COLLECTIBLES - 1) {
                            collectibles[collectibleCount] = new Seed(x, y);
                            if (collectibles[collectibleCount] != nullptr) {
                                collectibleCount++;
                            }
                        }
                        break;

                    case ' ':
                    case '\t':
                    case '\r':
                    case '\n':
                        // Skip whitespace
                        break;

                    default:
                        // Unknown character - not an error, just skip
                        break;
                    }
                }
                catch (const std::bad_alloc& e) {
                    std::cout << "MEMORY ERROR: Out of memory when creating object at (" << col << ", " << row << ")" << std::endl;
                    break; // Stop processing this row
                }
                catch (const std::exception& e) {
                    std::cout << "EXCEPTION while handling '" << ch << "' at (" << col << ", " << row << "): " << e.what() << std::endl;
                }
                catch (...) {
                    std::cout << "UNKNOWN EXCEPTION while handling '" << ch << "' at (" << col << ", " << row << ")" << std::endl;
                }
            }

            row++;

            // Force flush output to see progress
            std::cout.flush();
        }

        file.close();

        std::cout << "=== LoadWorldFromFile Completed Successfully ===" << std::endl;
        std::cout << "Final counts:" << std::endl;
        std::cout << "  Tiles: " << tileCount << "/" << MAX_TILES << std::endl;
        std::cout << "  Obstacles: " << obstacleCount << "/" << MAX_OBSTACLES << std::endl;
        std::cout << "  Collectibles: " << collectibleCount << "/" << MAX_COLLECTIBLES << std::endl;
        std::cout << "  Enemies: " << enemyCount << "/" << MAX_ENEMIES << std::endl;
        std::cout << "  Rows processed: " << row << std::endl;

        // Verify that we created objects successfully
        if (tileCount == 0 && obstacleCount == 0 && collectibleCount == 0 && enemyCount == 0) {
            std::cout << "WARNING: No objects were created! Check your texture files and map format." << std::endl;
        }
    }
};