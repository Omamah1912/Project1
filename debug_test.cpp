#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Duck Debug Test");
    
    // Load duck texture
    sf::Texture duckTexture;
    if (!duckTexture.loadFromFile("assets/duck_brown.png")) {
        std::cout << "ERROR: Failed to load duck texture!" << std::endl;
        return -1;
    }
    
    std::cout << "Duck texture loaded successfully!" << std::endl;
    std::cout << "Texture size: " << duckTexture.getSize().x << "x" << duckTexture.getSize().y << std::endl;
    
    // Create duck sprite
    sf::Sprite duckSprite;
    duckSprite.setTexture(duckTexture);
    duckSprite.setPosition(400, 300); // Center of screen
    duckSprite.setScale(2.0f, 2.0f);  // Make it big and visible
    
    std::cout << "Duck sprite created at position: (400, 300)" << std::endl;
    std::cout << "Duck sprite scale: 2.0x" << std::endl;
    
    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        // Clear screen with blue background
        window.clear(sf::Color(135, 206, 235));
        
        // Draw duck
        window.draw(duckSprite);
        
        // Display
        window.display();
    }
    
    return 0;
}