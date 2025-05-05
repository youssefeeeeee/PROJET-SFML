#include "Game.h"
//game.cpp
void Game::initWindow() {
    auto desktop = sf::VideoMode::getDesktopMode();
    window.create(desktop, "Racing Game", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
}

Game::Game() :
    obstacleSpawnInterval(2.0f) // Initialisation de l'intervalle
{
    initWindow();
    voiture.loadTexture("assets/voiture.png", this->window);
    background.load("assets/racing.jpg", window.getSize());
    ui.loadBackground("assets/bgui.jpg");

     //Initialisation des obstacles
    const int NUM_OBSTACLES = 5; // Nombre d'obstacles à précharger
    for (int i = 0; i < NUM_OBSTACLES; ++i) {
        Obstacle obstacle;
        if (obstacle.loadTexture("./assets/obstacle.png")) {
        
            obstacles.push_back(obstacle);
        }
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(
                    sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                ui.handleMouseClick(mousePos, window);
            }
        }
    }
}
void Game::update(float deltaTime) {
    if (ui.getCurrentState() == UI::GameState::PLAYING) {
        voiture.handleInput();
        voiture.setRoadWidth(background.getRoadWidth());
        voiture.update(deltaTime, window);
        background.update(deltaTime);

        // Mise à jour du score (exemple: basé sur le temps)
        static int score = 0;
        score += static_cast<int>(deltaTime * 10);
        ui.update(deltaTime, score);
    }
    if (ui.getCurrentState() == UI::GameState::PLAYING) {
        // Spawn des obstacles
        if (obstacleSpawnClock.getElapsedTime().asSeconds() > obstacleSpawnInterval) {
            for (auto& obs : obstacles) {
                if (!obs.getIsActive()) {
                    obs.spawn(background.getRoadWidth(), window.getSize().y);
                    break;
                }
            }
            obstacleSpawnClock.restart();
            // Rendre l'intervalle plus court au fil du temps pour augmenter la difficulté
            obstacleSpawnInterval = std::max(0.5f, obstacleSpawnInterval * 0.98f);
        }
        for (auto& obs : obstacles) {
            obs.update(deltaTime);

            // Détection de collision
            if (obs.checkCollision(voiture.getGlobalBounds())) {
                // Gérer la collision (game over ou vie perdue)
                ui.resetGame();
                ui.setCurrentState(UI::GameState::MENU);
                break;
            }
        }
    }
}
void Game::render() {
    window.clear();

    switch (ui.getCurrentState()) {
    case UI::GameState::MENU:
    case UI::GameState::SETTINGS:
        ui.drawBackground(window);
        ui.draw(window);
        break;

    case UI::GameState::PLAYING:
        background.draw(window);
        voiture.draw(window);
        for (const auto& obs : obstacles) {
            obs.draw(window);
        }
        ui.draw(window);
        break;
    }

    window.display();
}
void Game::run() {
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        handleEvents();
        update(deltaTime);
        render();
    }
}