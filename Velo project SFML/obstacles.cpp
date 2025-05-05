
#include <cmath>
#include "obstacles.h"
std::mt19937 Obstacle::randomEngine(std::random_device{}());
std::uniform_real_distribution<float> Obstacle::speedDistribution(150.0f, 300.0f);

Obstacle::Obstacle() : isActive(false), speed(0), isLeftLane(true) {}

bool Obstacle::loadTexture(const std::string& path) {
    if (!texture.loadFromFile(path)) return false;
    sprite.setTexture(texture);
    sprite.setScale(0.25f, 0.5f);
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height);
    return true;
}

void Obstacle::spawn(float roadWidth, float windowHeight) {
    isLeftLane = (rand() % 2 == 0); // 50% gauche, 50% droite
    speed = speedDistribution(randomEngine);

    float roadLeft = (1920.0f - roadWidth) / 2.0f; // Centrage de la route

    if (isLeftLane) {
        position.x = roadLeft + roadWidth * 0.25f; // Voie gauche
    }
    else {
        position.x = roadLeft + roadWidth * 0.75f; // Voie droite
    }

    position.y = -sprite.getGlobalBounds().height;
    sprite.setPosition(position);
    isActive = true;
}

void Obstacle::update(float deltaTime) {
    if (!isActive) return;

    position.y += speed * deltaTime;
    sprite.setPosition(position);

    if (position.y > 1200.0f) { // Hors écran
        isActive = false;
    }
}
void Obstacle::draw(sf::RenderTarget& target) const {
    if (isActive) {
        target.draw(sprite);
    }
}

bool Obstacle::checkCollision(const sf::FloatRect& bounds) const {
    if (!isActive) return false;
    return sprite.getGlobalBounds().intersects(bounds);
}

bool Obstacle::isOnScreen(float windowHeight) const {
    return position.y + sprite.getGlobalBounds().height > 0 &&
        position.y < windowHeight;
}

const sf::FloatRect Obstacle::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}
