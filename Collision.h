#pragma once
#include "Tile.h"

class CollisionManager {
public:
    static bool isCollidingWithSolid(const sf::Sprite& obj, Tile* tiles[], int tileCount) {
        sf::FloatRect objBounds = obj.getGlobalBounds();

        for (int i = 0; i < tileCount; i++) {
            if (!tiles[i]) continue;

            std::string tex = tiles[i]->getTextureName();


            if (tex == "assets/wall.jpg" || tex == "assets/ground.png") {
                if (objBounds.intersects(tiles[i]->getGlobalBounds())) {
                    return true;
                }
            }
        }
        return false;
    }
};
