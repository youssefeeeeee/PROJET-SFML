#include "Player.h"
#include <iostream> // Pour std::cerr

// Constructeur
Player::Player() : m_velocity(0.f, 0.f) { // Initialise la v�locit� � z�ro
    loadTexture(); // Charge la texture
    mcar.setTexture(m_texture); // Lie la texture charg�e au sprite mcar
    // Optionnel: D�finir une position initiale ou une origine si n�cessaire
    // mcar.setOrigin(mcar.getLocalBounds().width / 2.f, mcar.getLocalBounds().height / 2.f);
    // mcar.setPosition(100.f, 100.f); 
}

// Charge la texture
void Player::loadTexture() {
    if (!m_texture.loadFromFile("./Assets/voiture.png")) {
        std::cerr << "Failed to load player texture! (./Assets/voiture.png)\n";
        // G�rer l'erreur de mani�re appropri�e, exit() est un peu brutal
        // Vous pourriez lancer une exception ou d�finir un �tat d'erreur
        exit(EXIT_FAILURE);
    }
    // Optionnel: Lisser la texture si elle est agrandie/r�tr�cie
   // m_texture.setSmooth(true);
}

// G�re les entr�es clavier
void Player::handleInput() {
    m_velocity = { 0.f, 0.f }; // R�initialise la v�locit� � chaque frame

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        m_velocity.y = -m_speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        m_velocity.y = m_speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        m_velocity.x = -m_speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        m_velocity.x = m_speed;

    // Normalisation (optionnel, pour �viter mouvement diagonal plus rapide)
    // float length = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
    // if (length > 0) {
    //     m_velocity /= length; // Normalise le vecteur
    //     m_velocity *= m_speed; // Applique la vitesse
    // }
}

// Met � jour la position du sprite
void Player::update(float deltaTime) {
    // D�place le sprite en fonction de la v�locit� et du temps �coul�
    mcar.move(m_velocity * deltaTime);

    // --- Ajout possible : Limiter le mouvement � l'�cran ---
    // sf::FloatRect bounds = mcar.getGlobalBounds();
    // sf::Vector2f pos = mcar.getPosition();
    // 
    // // Limites (exemple pour une fen�tre 800x600)
    // float minX = 0; 
    // float maxX = 800.f - bounds.width;
    // float minY = 0;
    // float maxY = 600.f - bounds.height;
    // 
    // if (pos.x < minX) pos.x = minX;
    // if (pos.x > maxX) pos.x = maxX;
    // if (pos.y < minY) pos.y = minY;
    // if (pos.y > maxY) pos.y = maxY;
    // 
    // mcar.setPosition(pos);
    // ---------------------------------------------------------
}

// Dessine le sprite
void Player::draw(sf::RenderWindow& window) const {
    window.draw(mcar);
}

// Retourne les limites globales
sf::FloatRect Player::getBounds() const {
    return mcar.getGlobalBounds();
}

// D�finit la position
//void Player::setPosition(float x, float y) {
//    mcar.setPosition(x, y);
//}

//// D�finit la taille (via mise � l'�chelle)
//void Player::setSize(float width, float height) {
//    sf::FloatRect currentBounds = mcar.getLocalBounds();
//    if (currentBounds.width > 0 && currentBounds.height > 0) {
//        float scaleX = width / currentBounds.width;
//        float scaleY = height / currentBounds.height;
//        mcar.setScale(scaleX, scaleY);
//    }
//}