#pragma once
#include <SFML/Graphics.hpp>

class Back {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Shader parallaxShader;
    float offset;
    float scrollSpeed;

public:
    Back();
    bool load(const std::string& texturePath);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    void setScrollSpeed(float speed);
    void resizeToWindow(const sf::RenderWindow& window);
};