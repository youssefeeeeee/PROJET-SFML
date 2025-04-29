#include "voiture.h"
#include <SFML/Graphics.hpp>
#include <iostream>
voiture::voiture() : lateral(0.f), friction(0.88f), position(0.f, 0.f), acceleration(1200.f), maxSpeed(500.f){}
bool voiture::loadfromtxt(const std::string & path, sf::RenderWindow &window)  {
	if (!texture.loadFromFile(path)) {
		return false;
	}
    sprite.setTexture(texture);
	sprite.setScale({ 0.4f, 0.4f });
	sprite.setOrigin({ texture.getSize().x / 2.f,texture.getSize().y / 2.f });
    position = {400.f,300.f};
    sprite.setPosition(position);
	return true;
}



void voiture::draw(sf::RenderTarget& target) const {
    target.draw(sprite);
}



void voiture::handleInput() {
    // Tourner à gauche (flèche gauche)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		lateral -= acceleration ;
    }

    // Tourner à droite (flèche droite)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		lateral += acceleration;
    }

    // Limiter la vitesse maximale
    if (lateral > maxSpeed) lateral = maxSpeed;
    if (lateral < -maxSpeed) lateral = -maxSpeed;

}




void voiture::applyFriction(float deltaTime) {

    lateral *= friction;

    // Arrêt complet si vitesse très faible
    if (std::abs(lateral) < 1.f) {
        lateral = 0.f;
    }
}




void voiture::clampPosition() {
    // Calcul de la marge en fonction de la taille du sprite ou d'une valeur par défaut
    const float margin =  sprite.getGlobalBounds().width / 2.f;

    // Limites gauche et droite de l'écran (en supposant une largeur de 800 pixels)
    const float leftBound = margin;
    const float rightBound = 800.f - margin;

    // Correction de la position si nécessaire
    if (position.x < leftBound) {
        position.x = leftBound;
        lateral = 0.f;  // Arrêt du mouvement latéral
    }
    else if (position.x > rightBound) {
        position.x = rightBound;
        lateral = 0.f;  // Arrêt du mouvement latéral
    }
}


sf::FloatRect voiture::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}
void voiture::update(float deltaTime) {
    // Appliquer le mouvement
    position.x += lateral * deltaTime;

    // Appliquer la friction
    applyFriction(deltaTime);

    // Garder dans les limites
    clampPosition();

    // Mettre à jour le sprite
        sprite.setPosition(position);
}


