#include "voiture.h"
// voiture.cpp

Voiture::Voiture() : lateralSpeed(0.f), acceleration(1200.f), friction(0.88f),currentRoadWidth(0.f) {}

bool Voiture::loadTexture(const std::string& path,sf::RenderTarget &window) {
    if (!texture.loadFromFile(path)) return false;
    sprite.setTexture(texture);
    sprite.setScale(0.45f, 0.45f);
    sf::FloatRect bounds = sprite.getGlobalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height);
    position.x = window.getSize().x / 2.f;
    position.y = window.getSize().y - bounds.height / 2.f;
    sprite.setPosition(position);
    return true;
}
sf::FloatRect Voiture::getAdjustedBounds() const {
    auto bounds = sprite.getGlobalBounds();
    return {
        bounds.left + bounds.width * 0.1f,    // Compense les bords transparents
        bounds.top + bounds.height * 0.1f,    // Idem pour la hauteur
        bounds.width * 0.8f,                  // Largeur effective
        bounds.height * 0.8f                  // Hauteur effective
    };
}

void Voiture::handleInput() {
    lateralSpeed = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) lateralSpeed -= acceleration;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) lateralSpeed += acceleration;
}

void Voiture::applyFriction(float deltaTime) {
    lateralSpeed *= friction;
    if (std::abs(lateralSpeed) < 1.f) lateralSpeed = 0.f;
}

void Voiture::clampPosition(const sf::RenderWindow& window) {
    auto bounds = getAdjustedBounds();
    float effectiveWidth = bounds.width;
    float windowCenter = window.getSize().x / 2.0f;

    float leftBound = windowCenter - currentRoadWidth / 2 + effectiveWidth / 2;
    float rightBound = windowCenter + currentRoadWidth / 2 - effectiveWidth / 2;

    position.x = std::clamp(position.x, leftBound, rightBound);
    sprite.setPosition(position);

    // Debug visuel immédiat
    sf::RectangleShape leftMarker(sf::Vector2f(2.f, 50.f));
    leftMarker.setPosition(leftBound, position.y - 25.f);
    leftMarker.setFillColor(sf::Color::Green);
    const_cast<sf::RenderWindow&>(window).draw(leftMarker);

    sf::RectangleShape rightMarker(sf::Vector2f(2.f, 50.f));
    rightMarker.setPosition(rightBound, position.y - 25.f);
    rightMarker.setFillColor(sf::Color::Green);
    const_cast<sf::RenderWindow&>(window).draw(rightMarker);
}

void Voiture::update(float deltaTime, const sf::RenderWindow& window) {
    position.x += lateralSpeed * deltaTime;
    applyFriction(deltaTime);
    clampPosition(window); // Contient déjà setPosition
}

void Voiture::draw(sf::RenderTarget& target) const {
    target.draw(sprite); // Dessine la voiture
}
sf::FloatRect Voiture::getGlobalBounds() const {
    // Retourne les bounds avec une marge réduite pour un gameplay plus fair
    sf::FloatRect bounds = sprite.getGlobalBounds();
    float marginX = bounds.width * 0.2f; // Réduction de 20% en largeur
    float marginY = bounds.height * 0.1f; // Réduction de 10% en hauteur

    return sf::FloatRect(
        bounds.left + marginX / 2,
        bounds.top + marginY / 2,
        bounds.width - marginX,
        bounds.height - marginY
    );
}
