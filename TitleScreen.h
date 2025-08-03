#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class TitleScreen {
private:
    sf::RectangleShape background;
    sf::Font font;
    sf::Text titleText;
    sf::Text instructionText;
    float blinkTimer;

public:
    TitleScreen(sf::RenderWindow& window, const std::string& imagePath = "") {
        // Get window size
        sf::Vector2u windowSize = window.getSize();

        // Create background - try to load image, fallback to blue
        background.setSize(sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));
        background.setPosition(0, 0);

        if (!imagePath.empty()) {
            sf::Texture* bgTexture = new sf::Texture();
            if (bgTexture->loadFromFile(imagePath)) {
                background.setTexture(bgTexture);
                std::cout << "Title screen image loaded successfully: " << imagePath << std::endl;
            }
            else {
                background.setFillColor(sf::Color::Blue);
                std::cout << "Failed to load title image, using blue background" << std::endl;
                delete bgTexture;
            }
        }
        else {
            background.setFillColor(sf::Color::Blue);
        }

        // Initialize timer
        blinkTimer = 0.0f;

        // Load font
        if (!font.loadFromFile("assets/DejaVuSans-BoldOblique.ttf")) {
            std::cerr << "WARNING: Could not load font, using default font\n";
        }

        //// Setup title text
        //titleText.setFont(font);
        //titleText.setString("DUCK DASH");
        //titleText.setCharacterSize(80);
        //titleText.setFillColor(sf::Color::White);
        //titleText.setStyle(sf::Text::Bold);

        //// Center title text
        //sf::FloatRect titleBounds = titleText.getLocalBounds();
        //titleText.setOrigin(titleBounds.width / 2.0f, titleBounds.height / 2.0f);
        //titleText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

        // Setup instruction text
        instructionText.setFont(font);
        instructionText.setString("Press any key to continue...");
        instructionText.setCharacterSize(24);
        instructionText.setFillColor(sf::Color::Yellow);

        // Center instruction text
        sf::FloatRect instrBounds = instructionText.getLocalBounds();
        instructionText.setOrigin(instrBounds.width / 2.0f, instrBounds.height / 2.0f);
        instructionText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f + 100.0f);
    }

    bool handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::KeyPressed ||
            event.type == sf::Event::MouseButtonPressed) {
            return true;
        }
        return false;
    }

    void update(float dt) {
        blinkTimer += dt;

        // Make instruction text blink every 0.5 seconds
        if (static_cast<int>(blinkTimer / 0.5f) % 2 == 0) {
            instructionText.setFillColor(sf::Color::Yellow);
        }
        else {
            instructionText.setFillColor(sf::Color::Transparent);
        }
    }

    void render(sf::RenderWindow& window) {
        window.draw(background);
        window.draw(titleText);
        window.draw(instructionText);
    }
};