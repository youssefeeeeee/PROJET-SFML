#include "background.h"
// Background.cpp
Background::Background() : scrollSpeed(100.f), offset(0.f) {}

bool Background::load(const std::string& path, const sf::Vector2u& size) {
    if (!texture.loadFromFile(path)) return false;
    windowSize = size;
    texture.setRepeated(true);
    sprite.setTexture(texture);
    
    float scalex = static_cast<float>(windowSize.x) / texture.getSize().x;
	float scaley = static_cast<float>(windowSize.y) / texture.getSize().y;
    sprite.setScale(scalex, scaley);
    
    float visibleHeight = static_cast<float>(windowSize.y) / scaley;
    
    return true;
}

void Background::update(float deltaTime) {
    offset += scrollSpeed * deltaTime; // Chang� de -= � += pour inverser le d�filement
    float textureHeight = static_cast<float>(windowSize.y) / sprite.getScale().y;
    if (offset >= textureHeight) offset -= textureHeight; // Chang� la condition
    sprite.setPosition(0, offset); // Maintien de la position n�gative
}

void Background::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
    sf::Sprite secondSprite = sprite;
    float textureHeight = static_cast<float>(windowSize.y) / sprite.getScale().y;
    secondSprite.setPosition(0, sprite.getPosition().y - textureHeight); // Chang� de - � +
    window.draw(secondSprite);
}

float Background::getRoadWidth() const {
    // Mesure exacte de la partie "roulable"
    return texture.getSize().x * sprite.getScale().x * 0.68f; // Ajustement pr�cis
}

void Background::setScrollSpeed(float speed) {
    scrollSpeed = speed;
}