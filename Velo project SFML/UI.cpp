#include "ui.h"
#include <sstream>
#include <iomanip>

UI::UI() : score(0), time(0.0f), highscore(0), currentState(GameState::MENU), selectedDifficulty(0) {
    // Load font
    if (!font.loadFromFile("assets/arial.ttf")) {
        // Fallback if font loading fails
    }

    // Initialize menu buttons (Play, Settings, Quit)
    std::vector<std::string> buttonLabels = { "Play", "Settings", "Quit" };
    for (size_t i = 0; i < buttonLabels.size(); ++i) {
        sf::Text button;
        button.setFont(font);
        button.setCharacterSize(30);
        button.setFillColor(sf::Color::White);
        button.setString(buttonLabels[i]);
        button.setPosition(300.0f, 200.0f + i * 60.0f);
        menuButtons.push_back(button);
    }

    // Initialize in-game UI
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.0f, 10.0f);
    scoreText.setString("Score: 0");

    timeText.setFont(font);
    timeText.setCharacterSize(24);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(10.0f, 40.0f);
    timeText.setString("Time: 0.00");

    highscoreText.setFont(font);
    highscoreText.setCharacterSize(24);
    highscoreText.setFillColor(sf::Color::White);
    highscoreText.setPosition(10.0f, 70.0f);
    highscoreText.setString("Highscore: 0");

    // Initialize settings options (Difficulty: Easy, Medium, Hard; Back)
    std::vector<std::string> settingsLabels = { "Difficulty: Easy", "Difficulty: Medium", "Difficulty: Hard", "Back" };
    for (size_t i = 0; i < settingsLabels.size(); ++i) {
        sf::Text option;
        option.setFont(font);
        option.setCharacterSize(24);
        option.setFillColor(i == selectedDifficulty ? sf::Color::Yellow : sf::Color::White);
        option.setString(settingsLabels[i]);
        option.setPosition(300.0f, 200.0f + i * 40.0f);
        settingsOptions.push_back(option);
    }

    // Initialize settings highscore display
    settingsHighscoreText.setFont(font);
    settingsHighscoreText.setCharacterSize(24);
    settingsHighscoreText.setFillColor(sf::Color::White);
    settingsHighscoreText.setPosition(300.0f, 360.0f);
    settingsHighscoreText.setString("Highscore: 0");
}

bool UI::loadBackground(const std::string& path) {
    if (!txt.loadFromFile(path)) {
        return false;
    }
    txt.setSmooth(true); // Smooth texture scaling
    sprite.setTexture(txt);

    return true;
}

void UI::updateScale(const sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = txt.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    sprite.setScale(scaleX, scaleY);
}

void UI::update(float deltaTime, int currentScore) {
    if (currentState == GameState::PLAYING) {
        score = currentScore;
        scoreText.setString("Score: " + std::to_string(score));
        time += deltaTime;
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << time;
        timeText.setString("Time: " + ss.str());
        if (score > highscore) {
            highscore = score;
            highscoreText.setString("Highscore: " + std::to_string(highscore));
            settingsHighscoreText.setString("Highscore: " + std::to_string(highscore));
            updateHighscore();
        }
    }
}

void UI::draw(sf::RenderWindow& window) {
    switch (currentState) {
    case GameState::MENU:
        for (const auto& button : menuButtons) {
            window.draw(button);
        }
        break;
    case GameState::PLAYING:
        window.draw(scoreText);
        window.draw(timeText);
        window.draw(highscoreText);
        break;
    case GameState::SETTINGS:
        for (const auto& option : settingsOptions) {
            window.draw(option);
        }
        window.draw(settingsHighscoreText);
        break;
    }
}

void UI::drawBackground(sf::RenderWindow& window) {
    updateScale(window);
    window.draw(sprite);
}

bool UI::isButtonClicked(const sf::Text& button, const sf::Vector2f& mousePos) {
    return button.getGlobalBounds().contains(mousePos);
}

void UI::handleMouseClick(sf::Vector2f mousePos, sf::RenderWindow& window) {
    if (currentState == GameState::MENU) {
        if (isButtonClicked(menuButtons[0], mousePos)) {
            currentState = GameState::PLAYING;
            time = 0.0f;
            score = 0;
        }
        else if (isButtonClicked(menuButtons[1], mousePos)) {
            currentState = GameState::SETTINGS;
        }
        else if (isButtonClicked(menuButtons[2], mousePos)) {
            window.close();
        }
    }
    else if (currentState == GameState::SETTINGS) {
        for (size_t i = 0; i < settingsOptions.size(); ++i) {
            if (isButtonClicked(settingsOptions[i], mousePos)) {
                if (i < 3) {
                    selectedDifficulty = i;
                    for (size_t j = 0; j < 3; ++j) {
                        settingsOptions[j].setFillColor(j == selectedDifficulty ? sf::Color::Yellow : sf::Color::White);
                    }
                }
                else if (i == 3) {
                    currentState = GameState::MENU;
                }
            }
        }
    }
}

UI::GameState UI::getCurrentState() const {
    return currentState;
}

int UI::getSelectedDifficulty() const {
    return selectedDifficulty;
}

int UI::getHighscore() const {
    return highscore;
}

void UI::updateHighscore() {
    // Could save highscore to a file here
}
void UI::resetGame() {
    time = 0.0f;
    score = 0;
    scoreText.setString("Score: 0");
    timeText.setString("Time: 0.00");
}
void UI::setCurrentState(GameState newState) {
    currentState = newState;

    // Réinitialisations spécifiques selon l'état
    if (newState == GameState::PLAYING) {
        time = 0.0f;
        score = 0;
        scoreText.setString("Score: 0");
        timeText.setString("Time: 0.00");
    }
}