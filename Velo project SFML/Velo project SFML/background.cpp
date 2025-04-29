#include "background.h"
#include <iostream>

Back::Back() : offset(0.f), scrollSpeed(50.f) {
    // Chargez le shader directement dans le constructeur
    if (!parallaxShader.loadFromMemory(
        "uniform float offset;"
        "void main() {"
        "    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
        "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
        "    gl_TexCoord[0].y = gl_TexCoord[0].y - offset;" // Changé '+' par '-' pour inverser la direction
        "    gl_FrontColor = gl_Color;"
        "}", sf::Shader::Vertex)) {
        std::cerr << "Failed to load parallax shader" << std::endl;
    }
}

bool Back::load(const std::string& texturePath) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load background texture" << std::endl;
        return false;
    }
    texture.setRepeated(true);
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255, 255, 255, 220)); // Légère transparence
    return true;
}

void Back::resizeToWindow(const sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u texSize = texture.getSize();

    // Ajuste la texture pour couvrir toute la fenêtre
    sprite.setScale(
        windowSize.x / static_cast<float>(texSize.x),
        windowSize.y / static_cast<float>(texSize.y)
    );
}

void Back::update(float deltaTime) {
    // Défilement vertical vers le bas
    offset += scrollSpeed * deltaTime / 1000.f;

    // Réinitialisation pour bouclage infini
    if (offset > 1.0f) {
        offset -= 1.0f;
    }

    parallaxShader.setUniform("offset", offset);
}

void Back::draw(sf::RenderWindow& window) const {
    window.draw(sprite, &parallaxShader);
}

void Back::setScrollSpeed(float speed) {
    scrollSpeed = speed;
}