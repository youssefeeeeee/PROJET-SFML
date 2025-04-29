#pragma once
#ifndef VOITURE_H
#define VOITURE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <SFML/Window.hpp>
class voiture
{
private :
	sf::Texture texture;//pour la voiture
	sf::Sprite sprite;
    float acceleration;
    float maxSpeed;
	float lateral;//pour la vitesse de rotation
    void applyFriction(float deltaTime);//Ralentir progressivement la voiture quand elle n'accélère plus pour un mouvement plus réaliste.
    void clampPosition();//Empêcher la voiture de sortir de l'écran.
    float friction;
    sf::Vector2f position;

public :
	voiture();
	bool loadfromtxt(const std::string& path, sf::RenderWindow& window);//Charge la texture de la voiture et configure son sprite.
	void draw(sf::RenderTarget& target) const;//pour dessiner la voiture
	void handleInput();//pour gérer les entrées de l'utilisateur
    sf::FloatRect getGlobalBounds() const;
    void update(float deltatime);

};

#endif