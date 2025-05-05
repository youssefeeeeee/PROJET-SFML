#ifndef BACKGROUND_H
#define BACKGROUND_H
// Background.h
#include <SFML/Graphics.hpp>

class Background {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float scrollSpeed;
    float offset;
    sf::Vector2u windowSize;

public:
    Background();
    bool load(const std::string& path, const sf::Vector2u& size);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    float getRoadWidth() const;
    void setScrollSpeed(float speed); // Nouvelle méthode pour ajuster la vitesse
};

#endif