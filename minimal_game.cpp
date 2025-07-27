#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Duck Game - Minimal");
    window.setFramerateLimit(60);

    // Load duck texture
    sf::Texture duckTexture;
    if (!duckTexture.loadFromFile("assets/duck_brown.png")) {
        std::cout << "ERROR: Failed to load duck texture!" << std::endl;
        return -1;
    }

    // Create duck sprite
    sf::Sprite duck;
    duck.setTexture(duckTexture);
    duck.setScale(2.0f, 2.0f);  // Make it large
    duck.setPosition(400, 200); // Center horizontally, high up

    // Duck movement variables
    float duckSpeed = 200.0f;
    float duckVelY = 0.0f;
    float gravity = 800.0f;
    float groundY = 450.0f;

    sf::Clock clock;

    std::cout << "Game started! Use arrow keys to move the duck." << std::endl;
    std::cout << "Duck should be visible at position (400, 200)" << std::endl;

    // Game loop
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Get current duck position
        sf::Vector2f duckPos = duck.getPosition();
        std::cout << "Duck at: (" << duckPos.x << ", " << duckPos.y << ")" << std::endl;

        // Handle input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            duck.move(-duckSpeed * dt, 0);
            std::cout << "Moving left" << std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            duck.move(duckSpeed * dt, 0);
            std::cout << "Moving right" << std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (duckPos.y >= groundY - 10) { // Only jump if on ground
                duckVelY = -400.0f; // Jump velocity
                std::cout << "Jumping!" << std::endl;
            }
        }

        // Apply gravity
        duckVelY += gravity * dt;
        duck.move(0, duckVelY * dt);

        // Keep duck above ground
        duckPos = duck.getPosition();
        if (duckPos.y > groundY) {
            duck.setPosition(duckPos.x, groundY);
            duckVelY = 0;
        }

        // Keep duck on screen horizontally
        if (duckPos.x < 0) duck.setPosition(0, duckPos.y);
        if (duckPos.x > 800) duck.setPosition(800, duckPos.y);

        // Render
        window.clear(sf::Color(135, 206, 235)); // Sky blue

        // Draw ground
        sf::RectangleShape ground(sf::Vector2f(800, 150));
        ground.setFillColor(sf::Color::Green);
        ground.setPosition(0, groundY);
        window.draw(ground);

        // Draw duck
        window.draw(duck);

        // Draw debug circle around duck
        sf::CircleShape debugCircle(50);
        debugCircle.setFillColor(sf::Color(255, 0, 0, 100)); // Semi-transparent red
        debugCircle.setPosition(duckPos.x - 25, duckPos.y - 25);
        window.draw(debugCircle);

        window.display();
    }

    std::cout << "Game ended." << std::endl;
    return 0;
}