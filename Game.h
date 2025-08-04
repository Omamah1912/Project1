#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Duck.h"
#include "Obstacle.h"
#include "Collectible.h"
#include "Juice.h"
#include "Enemy.h"
#include "WorldLoader.h"
#include "Tornado.h"
#include "GameState.h"
#include "TitleScreen.h"
#include "Menu.h"
#include <fstream> 

class Game {
private:
    sf::RenderWindow window;
    Duck player;
    sf::Clock clock;
    sf::Font font;

    // HUD
    sf::Text scoreText;
    sf::Text boostText;
    sf::Text livesText;
    bool showBoostText = false;
    float boostTextTimer = 0.0f;

    // Score display for VIEW state
    sf::Text viewScoreText;
    sf::Text backInstructionText;
    int lastScore;

    // Ability icon
    sf::Texture abilityIconTex;
    sf::Sprite abilityIcon;

    // Game world
    Tile* tiles[MAX_TILES];
    int tileCount;
    Obstacle* obstacles[MAX_OBSTACLES];
    int obstacleCount;
    Collectible* collectibles[MAX_COLLECTIBLES];
    int collectibleCount;
    Enemy* enemies[MAX_ENEMIES];
    int enemyCount;
    WorldLoader loader;

    sf::View camera;
    float worldWidth, worldHeight;

    // Game flow
    GameState gameState;
    TitleScreen titleScreen;
    Menu menu;

    // Flag to track if game world is initialized
    bool gameWorldInitialized;
    sf::Vector2f duckpos;


public:
    Game() : window(sf::VideoMode(1280, 720), "Duck Dash"),
        gameState(GameState::TITLE),
        titleScreen(window, "assets/d.png"),      // Load title image
        menu(window, "assets/a.jpg"),           // Load menu image
        gameWorldInitialized(false),
        lastScore(0) {
        // Only initialize basic UI elements, NOT the game world
        initializeUI();
    }

    ~Game() {
        cleanup();
    }

    void run() {
        while (window.isOpen()) {
            float dt = clock.restart().asSeconds();
            if (dt > 1.0f / 30.0f) dt = 1.0f / 60.0f;

            handleEvents();
            update(dt);
            render();
        }
    }

private:

    void initializeUI() {
        initFonts();
        initHUD();
        initAbilityIcon();
        initArrays();
        window.setFramerateLimit(60);
    }


    void initializeGameWorld() {
        std::cout << "Initializing game world..." << std::endl;

        cleanup();

        loadWorld();
        player.setSpawnPosition(duckpos);
        player.setPosition(duckpos.x, duckpos.y);
        calculateWorldBounds();
        initCamera();

        gameWorldInitialized = true;
        std::cout << "Game world initialized successfully!" << std::endl;
        std::cout << "Duck positioned at: (" << duckpos.x << ", " << duckpos.y << ")" << std::endl;
    }

    void initFonts() {
        if (!font.loadFromFile("assets/DejaVuSans-BoldOblique.ttf")) {
            std::cerr << "ERROR: Could not load font\n";
        }
    }

    void initHUD() {
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(700, 10);

        livesText.setFont(font);
        livesText.setCharacterSize(24);
        livesText.setFillColor(sf::Color::Red);
        livesText.setPosition(50, 10);

        boostText.setFont(font);
        boostText.setCharacterSize(24);
        boostText.setFillColor(sf::Color::Black);
        boostText.setString("Speed Boosted!");

        viewScoreText.setFont(font);
        viewScoreText.setCharacterSize(48);
        viewScoreText.setFillColor(sf::Color::White);

        backInstructionText.setFont(font);
        backInstructionText.setCharacterSize(24);
        backInstructionText.setFillColor(sf::Color::Yellow);
        backInstructionText.setString("Press ESC to go back to menu");
        backInstructionText.setPosition(400, 500);
    }

    void initAbilityIcon() {
        if (abilityIconTex.loadFromFile("assets/windshield.jpg")) {
            abilityIcon.setTexture(abilityIconTex);
            abilityIcon.setScale(0.05f, 0.05f);
            abilityIcon.setPosition(900, 10);
        }
    }

    void initArrays() {
        for (int i = 0; i < MAX_TILES; i++) tiles[i] = nullptr;
        for (int i = 0; i < MAX_OBSTACLES; i++) obstacles[i] = nullptr;
        for (int i = 0; i < MAX_COLLECTIBLES; i++) collectibles[i] = nullptr;
        for (int i = 0; i < MAX_ENEMIES; i++) enemies[i] = nullptr;
        tileCount = obstacleCount = collectibleCount = enemyCount = 0;
    }

    void saveScoreToFile(int score) {
        std::ofstream file("score.txt", std::ios::app); 
        if (file.is_open()) {
            file << score << "\n";
            file.close();
        }
        else {
            std::cerr << "Error: Could not open score.txt for writing.\n";
        }
    }

    void loadLastScore() {
        std::ifstream file("score.txt");
        lastScore = 0;
        if (file.is_open()) {

            std::string line;
            while (std::getline(file, line)) {
                if (!line.empty()) {
                    lastScore = std::stoi(line);
                }
            }
            file.close();
        }


        viewScoreText.setString("Last Score: " + std::to_string(lastScore));

        sf::FloatRect textBounds = viewScoreText.getLocalBounds();
        viewScoreText.setPosition(640 - textBounds.width / 2, 300);

        std::cout << "Last score loaded: " << lastScore << "\n";
    }

    void loadWorld() {
        loader.LoadWorldFromFile(
            "assets/temp.txt",
            tiles, tileCount,
            obstacles, obstacleCount,
            collectibles, collectibleCount,
            enemies, enemyCount, duckpos
        );
    }

    void initCamera() {
        camera.setSize(1024.0f, 768.0f);
        camera.setCenter(player.getPosition().x, player.getPosition().y - 100.0f);
        window.setView(camera);
    }

    void cleanup() {
        if (gameWorldInitialized) {  
            std::cout << "Cleaning up game world..." << std::endl;
            for (int i = 0; i < tileCount; i++) delete tiles[i];
            for (int i = 0; i < obstacleCount; i++) delete obstacles[i];
            for (int i = 0; i < collectibleCount; i++) delete collectibles[i];
            for (int i = 0; i < enemyCount; i++) delete enemies[i];
            initArrays(); // Reset arrays after cleanup
            std::cout << "Game world cleaned up." << std::endl;
        }
    }

    void handleEvents() {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }

            switch (gameState) {
            case GameState::TITLE:
                if (titleScreen.handleEvent(e)) {
                    gameState = GameState::MENU;
                }
                break;

            case GameState::MENU: {
                int sel = menu.handleEvent(e, window);
                if (sel == 0) {  // Start Game
                    std::cout << "Starting game..." << std::endl;
                    initializeGameWorld(); // Initialize game world only when starting
                    gameState = GameState::PLAY;
                    std::cout << "Game state changed to PLAY" << std::endl;
                }
                else if (sel == 1) { // View Score
                    gameState = GameState::VIEW;
                    loadLastScore(); // Load and display the score
                }
                else if (sel == 2) { // Quit
                    std::cout << "Quit selected" << std::endl;
                    window.close();
                }
                break;
            }

            case GameState::VIEW:
                // Handle going back to menu from score view
                if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
                    gameState = GameState::MENU;
                }
                break;

            case GameState::PLAY:
                if (gameWorldInitialized) {
                    player.setWindShield(sf::Keyboard::isKeyPressed(sf::Keyboard::S));
                }
                if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
                    // Save score before quitting
                    saveScore(player.getScore());

                    // Go back to menu
                    gameState = GameState::MENU;
                }
                break;

            default:
                break;
            }
        }
    }

    void update(float dt) {
        switch (gameState) {
        case GameState::TITLE:
            titleScreen.update(dt);
            break;

        case GameState::MENU:
            menu.update(dt);
            break;

        case GameState::VIEW:
            // No update needed for score view, it's static
            break;

        case GameState::PLAY:
            if (gameWorldInitialized) {
                player.update(dt);
                updateEnemies(dt);
                processCollisions(dt);
                updateCamera();
                updateHUD(dt);

                if (player.getLives() <= 0) {
                    saveScoreToFile(player.getScore());
                    gameState = GameState::MENU;
                }
            }
            break;

        default:
            break;
        }
    }

    void saveScore(int score) {
        std::ofstream file("score.txt");
        if (file.is_open()) {
            file << score;
            file.close();
            std::cout << "Score saved: " << score << "\n";
        }
        else {
            std::cerr << "Failed to save score!\n";
        }
    }

    void updateEnemies(float dt) {
        for (int i = 0; i < enemyCount; ++i) {
            if (auto bear = dynamic_cast<Bear*>(enemies[i])) {
                bear->setDuckInfo(player.getPosition(), player.isInPuddle());
            }
            enemies[i]->update(dt);
        }
    }

    void processCollisions(float dt) {
        handleTileCollisions(dt);
        handleObstacleCollisions();
        handleCollectibleCollisions();
        handleEnemyCollisions();
        updateObstacles(dt);
    }

    void updateObstacles(float dt) {
        for (int i = 0; i < obstacleCount; i++)
            if (obstacles[i]) obstacles[i]->update(dt);
    }

    void handleTileCollisions(float dt) {
        sf::Vector2f pos = player.getPosition();
        pos.x += player.getVelocityX() * dt;
        pos.y += player.getVelocityY() * dt;
        player.setPosition(pos.x, pos.y);

        sf::FloatRect duckBounds = player.getBounds();
        for (int i = 0; i < tileCount; ++i) {
            if (!tiles[i] || !tiles[i]->isSolid()) continue;
            sf::FloatRect tileBounds = tiles[i]->getBounds();
            sf::FloatRect intersection;
            if (duckBounds.intersects(tileBounds, intersection)) {
                if (intersection.width < intersection.height) {
                    pos.x += (duckBounds.left < tileBounds.left) ? -intersection.width : intersection.width;
                    player.setVelocityX(0);
                }
                else {
                    pos.y += (duckBounds.top < tileBounds.top) ? -intersection.height : intersection.height;
                    player.setVelocityY(0);
                    if (duckBounds.top < tileBounds.top) player.setOnGround(true, tileBounds.top);
                }
                player.setPosition(pos.x, pos.y);
                duckBounds = player.getBounds();
            }
        }
    }

    void handleObstacleCollisions() {
        sf::FloatRect duckBounds = player.getBounds();
        for (int i = 0; i < obstacleCount; i++) {
            if (obstacles[i] && duckBounds.intersects(obstacles[i]->getBounds())) {
                if (auto tornado = dynamic_cast<Tornado*>(obstacles[i])) {
                    if (tornado->shouldPushDuck(player.getPosition())) {
                        player.applyImpulse((player.getPosition().x < tornado->getPosition().x ? -150.f : 150.f), -100.f);
                    }
                }
            }
        }
    }

    void handleCollectibleCollisions() {
        sf::FloatRect duckBounds = player.getBounds();
        for (int i = 0; i < collectibleCount; i++) {
            if (collectibles[i] && duckBounds.intersects(collectibles[i]->getBounds())) {
                if (auto juice = dynamic_cast<Juice*>(collectibles[i])) {
                    player.applyJuiceBoost();
                    showBoostText = true;
                    boostTextTimer = 2.0f;
                }
                collectibles[i]->onCollect(player);
                delete collectibles[i];
                collectibles[i] = nullptr;
            }
        }
    }

    void handleEnemyCollisions() {
        sf::FloatRect duckBounds = player.getBounds();
        for (int i = 0; i < enemyCount; i++) {
            if (auto bear = dynamic_cast<Bear*>(enemies[i])) {
                if (duckBounds.intersects(bear->getBounds()) && bear->isChasing()) {
                    player.loseLife();
                    float knockX = (player.getPosition().x < bear->getPosition().x) ? -200.f : 200.f;
                    player.applyImpulse(knockX, -150.f);
                }
            }
        }
    }

    void updateCamera() {
        sf::Vector2f duckPos = player.getPosition();
        sf::Vector2f targetCenter(duckPos.x, duckPos.y - 100.0f);
        sf::Vector2f currentCenter = camera.getCenter();
        sf::Vector2f newCenter = currentCenter + (targetCenter - currentCenter) * 3.0f * (1.0f / 60.0f);

        float hw = camera.getSize().x / 2.0f;
        float hh = camera.getSize().y / 2.0f;

        if (newCenter.x - hw < 0) newCenter.x = hw;
        if (newCenter.x + hw > worldWidth) newCenter.x = worldWidth - hw;
        if (newCenter.y - hh < 0) newCenter.y = hh;
        if (newCenter.y + hh > worldHeight) newCenter.y = worldHeight - hh;

        camera.setCenter(newCenter);
        window.setView(camera);
    }

    void updateHUD(float dt) {
        if (showBoostText) {
            boostTextTimer -= dt;
            if (boostTextTimer <= 0) showBoostText = false;
        }
    }

    void render() {
        window.clear(sf::Color(135, 206, 235));

        switch (gameState) {
        case GameState::TITLE:
            // Reset to default view for UI rendering
            window.setView(window.getDefaultView());
            titleScreen.render(window);
            break;

        case GameState::MENU:
            // Reset to default view for UI rendering
            window.setView(window.getDefaultView());
            menu.render(window);
            break;

        case GameState::VIEW:
            // Reset to default view for score display
            window.setView(window.getDefaultView());
            // Draw score display
            window.draw(viewScoreText);
            window.draw(backInstructionText);
            break;

        case GameState::PLAY:
            if (gameWorldInitialized) {
                // Use game camera for world rendering
                window.setView(camera);
                drawWorld();
                player.render(window);

                // Switch back to default view for HUD
                window.setView(window.getDefaultView());

                scoreText.setString("Score: " + std::to_string(player.getScore()));
                window.draw(scoreText);
                if (showBoostText) window.draw(boostText);

                abilityIcon.setColor(player.isWindShieldActive() ? sf::Color::White : sf::Color(255, 255, 255, 150));
                window.draw(abilityIcon);

                livesText.setString("Lives: " + std::to_string(player.getLives()));
                window.draw(livesText);
            }
            break;

        default:
            break;
        }

        window.display();
    }

    void drawWorld() {
        sf::Vector2f camC = camera.getCenter();
        sf::Vector2f camS = camera.getSize();
        float left = camC.x - camS.x / 2.0f - 100.0f;
        float right = camC.x + camS.x / 2.0f + 100.0f;
        float top = camC.y - camS.y / 2.0f - 100.0f;
        float bottom = camC.y + camS.y / 2.0f + 100.0f;

        auto renderIfVisible = [&](auto objArray, int count) {
            for (int i = 0; i < count; i++) {
                if (objArray[i]) {
                    sf::Vector2f pos = objArray[i]->getPosition();
                    if (pos.x >= left && pos.x <= right && pos.y >= top && pos.y <= bottom) {
                        objArray[i]->render(window);
                    }
                }
            }
            };

        renderIfVisible(tiles, tileCount);
        renderIfVisible(obstacles, obstacleCount);
        renderIfVisible(collectibles, collectibleCount);
        renderIfVisible(enemies, enemyCount);
    }

    void calculateWorldBounds() {
        worldWidth = worldHeight = 0;
        for (int i = 0; i < tileCount; i++) {
            if (tiles[i]) {
                auto pos = tiles[i]->getPosition();
                auto bounds = tiles[i]->getBounds();
                worldWidth = std::max(worldWidth, pos.x + bounds.width);
                worldHeight = std::max(worldHeight, pos.y + bounds.height);
            }
        }
    }

    void positionDuckOnGround() {
        for (int i = 0; i < tileCount; i++) {
            if (tiles[i] && tiles[i]->getTextureName() == "assets/ground.png") {
                auto tilePos = tiles[i]->getPosition();
                player.setPosition(tilePos.x, tilePos.y - 48.0f);
                break;
            }
        }
    }
};