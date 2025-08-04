#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class Menu {
private:
    sf::RectangleShape background;
    sf::Font font;
    std::vector<sf::Text> options;
    std::vector<sf::Vector2f> originalPositions;
    std::vector<bool> isClicked;
    std::vector<float> clickTimers;
    int selectedIndex;
    int windowWidth, windowHeight;

public:
    Menu(const sf::RenderWindow& window, const std::string& bgPath = "") {
        // Get window size
        sf::Vector2u windowSize = window.getSize();
        windowWidth = windowSize.x;
        windowHeight = windowSize.y;


        background.setSize(sf::Vector2f(static_cast<float>(windowWidth), static_cast<float>(windowHeight)));
        background.setPosition(0, 0);

        if (!bgPath.empty()) {
            sf::Texture* bgTexture = new sf::Texture();
            if (bgTexture->loadFromFile(bgPath)) {
                background.setTexture(bgTexture);
                std::cout << "Menu background image loaded successfully: " << bgPath << std::endl;
            }
            else {
                background.setFillColor(sf::Color::Yellow);
                std::cout << "Failed to load menu image, using yellow background" << std::endl;
                delete bgTexture;
            }
        }
        else {
            background.setFillColor(sf::Color::Yellow);
        }

        selectedIndex = -1;

        // Load font
        if (!font.loadFromFile("assets/DejaVuSans-BoldOblique.ttf")) {
            std::cerr << "WARNING: Could not load font, using default font\n";
        }

        // Create menu options
        std::vector<std::string> labels = { "Start Game", "View Score", "Quit" };
        options.clear();
        originalPositions.clear();
        isClicked.clear();
        clickTimers.clear();

        for (size_t i = 0; i < labels.size(); i++) {
            sf::Text text;
            text.setFont(font);
            text.setString(labels[i]);
            text.setCharacterSize(48);
            text.setFillColor(sf::Color::White);
            text.setStyle(sf::Text::Bold);

            // Center each option
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);

            sf::Vector2f position(windowWidth / 2.0f, windowHeight / 2.0f + (i - 1) * 80.0f);
            text.setPosition(position);

            options.push_back(text);
            originalPositions.push_back(position);
            isClicked.push_back(false);
            clickTimers.push_back(0.0f);
        }
    }

    int handleEvent(sf::Event& event, sf::RenderWindow& window) {
        if (event.type == sf::Event::MouseMoved) {
            sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
            selectedIndex = -1;

            for (size_t i = 0; i < options.size(); i++) {
                if (options[i].getGlobalBounds().contains(mousePos)) {
                    selectedIndex = static_cast<int>(i);
                    break;
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left && selectedIndex != -1) {
                // Trigger click animation
                isClicked[selectedIndex] = true;
                clickTimers[selectedIndex] = 0.0f;
                return selectedIndex;
            }
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                if (selectedIndex > 0) {
                    selectedIndex--;
                }
                else {
                    selectedIndex = static_cast<int>(options.size()) - 1;
                }
            }
            else if (event.key.code == sf::Keyboard::Down) {
                if (selectedIndex < static_cast<int>(options.size()) - 1) {
                    selectedIndex++;
                }
                else {
                    selectedIndex = 0;
                }
            }
            else if (event.key.code == sf::Keyboard::Enter) {
                if (selectedIndex == -1) selectedIndex = 0;
                // Trigger click animation
                isClicked[selectedIndex] = true;
                clickTimers[selectedIndex] = 0.0f;
                return selectedIndex;
            }
            else if (selectedIndex == -1) {
                selectedIndex = 0;
            }
        }

        return -1;
    }

    void update(float dt) {
        // Update click animations
        for (size_t i = 0; i < options.size(); i++) {
            if (isClicked[i]) {
                clickTimers[i] += dt;

                // Float up animation for 0.5 seconds
                if (clickTimers[i] < 0.5f) {
                    float floatAmount = clickTimers[i] * 60.0f; // Float up 30 pixels over 0.5 seconds
                    options[i].setPosition(originalPositions[i].x, originalPositions[i].y - floatAmount);
                    options[i].setFillColor(sf::Color::Red);
                }
                else {
                    // Reset after animation
                    isClicked[i] = false;
                    options[i].setPosition(originalPositions[i]);
                    options[i].setFillColor(sf::Color::White);
                }
            }
        }
    }

    void render(sf::RenderWindow& window) {
        // Draw background
        window.draw(background);

        // Draw menu options
        for (size_t i = 0; i < options.size(); i++) {
            // Set color based on selection and click state
            if (!isClicked[i]) {
                if (static_cast<int>(i) == selectedIndex) {
                    options[i].setFillColor(sf::Color::Black); // Highlight selected option
                }
                else {
                    options[i].setFillColor(sf::Color::White);
                }
            }

            window.draw(options[i]);
        }
    }
};