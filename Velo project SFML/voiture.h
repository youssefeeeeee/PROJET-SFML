#pragma once
#include <SFML/Graphics.hpp>
//voitur.h
class Voiture {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float lateralSpeed;
    float acceleration;
    float friction;
    sf::Vector2f position;
    sf::FloatRect getAdjustedBounds() const;
    float currentRoadWidth;
    void applyFriction(float deltaTime);
    void clampPosition(const sf::RenderWindow& window);
public:
    Voiture();
    void setRoadWidth(float width) { currentRoadWidth = width; }
    bool loadTexture(const std::string& path,sf::RenderTarget& window);
    void handleInput();
    void update(float deltaTime, const sf::RenderWindow& window);
    void draw(sf::RenderTarget& target) const;
    sf::FloatRect getGlobalBounds() const;
};