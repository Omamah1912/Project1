#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameSimple.h"

int main() {
    std::cout << "Starting Duck Game Simple..." << std::endl;
    
    try {
        GameSimple game;
        game.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    
    std::cout << "Duck Game Simple ended." << std::endl;
    return 0;
}