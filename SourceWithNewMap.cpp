#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameFixed.h"

int main() {
    std::cout << "Starting Duck Game with New Map..." << std::endl;
    
    try {
        GameFixed game;
        game.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    
    std::cout << "Duck Game ended." << std::endl;
    return 0;
}