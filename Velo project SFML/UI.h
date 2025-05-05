#ifndef UI_H
#define UI_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class UI {
public:
    enum class GameState { MENU, PLAYING, SETTINGS };

private:
    sf::Font font;
    // Menu elements
    std::vector<sf::Text> menuButtons;
    // In-game UI elements
    sf::Text scoreText;
    sf::Text timeText;
    sf::Text highscoreText;
    // Settings elements
    std::vector<sf::Text> settingsOptions;
    sf::Text settingsHighscoreText;
    // Game state
    GameState currentState;
    int score;
    float time;
    int highscore;
    sf::Texture txt;
    sf::Sprite sprite;
    // Selected difficulty (0: Easy, 1: Medium, 2: Hard)
    int selectedDifficulty;

    bool isButtonClicked(const sf::Text& button, const sf::Vector2f& mousePos);

public:
    UI();
    void update(float deltaTime, int currentScore);
    void draw(sf::RenderWindow& window);
    bool loadBackground(const std::string& path);
    void updateScale(const sf::RenderWindow& window);
    void handleMouseClick(sf::Vector2f mousePos, sf::RenderWindow& window);
    GameState getCurrentState() const;
    int getSelectedDifficulty() const;
    int getHighscore() const;
    void updateHighscore();
    void drawBackground(sf::RenderWindow& window);
    void resetGame();
    void setCurrentState(GameState newState);
};

#endif