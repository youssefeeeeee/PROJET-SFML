#ifndef GAME_H
#define GAME_H
//Game.h
#include <SFML/Graphics.hpp>
#include "voiture.h"
#include "background.h"
#include "UI.h"
#include "obstacles.h"
class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    Voiture voiture;
    Background background;
    UI ui;  // Ajout de l'UI
    std::vector<Obstacle> obstacles;
    sf::Clock obstacleSpawnClock;
    float obstacleSpawnInterval;

    void initWindow();
    void handleEvents();
    void update(float deltaTime);
    void render();

public:
    Game();
    void run();
};

#endif