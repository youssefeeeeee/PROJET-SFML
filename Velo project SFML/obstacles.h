#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>
#include <random>

class Obstacle {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float speed;
    sf::Vector2f position;
    bool isActive;
    bool isLeftLane; // true: gauche, false: droite

    // Générateur aléatoire
    static std::mt19937 randomEngine;
    static std::uniform_real_distribution<float> speedDistribution;

public:
    Obstacle();

    bool loadTexture(const std::string& path);
    void spawn(float roadWidth, float windowHeight);
    void update(float deltaTime);
    void draw(sf::RenderTarget& target) const;

    bool checkCollision(const sf::FloatRect& bounds) const;
    bool getIsActive() const { return isActive; }
    bool isOnScreen(float windowHeight) const;
    const sf::FloatRect getGlobalBounds() const;
};

#endif