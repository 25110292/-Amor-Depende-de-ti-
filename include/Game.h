#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <optional>
#include <stack>
#include "Player.h"
#include "EventManager.h"
#include "Event.h"

enum class GameState {
    COVER,
    INPUT_NAME,
    INPUT_GENDER,
    INPUT_LOVE_NAME,
    PLAYING,
    PAUSED,
    SHOWING_FINAL,
    SHOWING_CREDITS
};

// Guarda el estado de un evento para poder regresar
struct EventSnapshot {
    int eventId;
    int totalPoints;
    int psychopathCount;
    int eventCount;
};

class Game {
private:
    sf::RenderWindow window;
    Player player;
    EventManager eventManager;

    int currentEventId;
    GameState state;
    GameState previousState;

    sf::Font font;
    sf::Texture backgroundTexture;
    std::optional<sf::Sprite> backgroundSprite;
    std::string lastLoadedImagePath;

    std::vector<sf::RectangleShape> optionButtons;
    std::vector<sf::Text> optionTexts;
    std::string inputBuffer;

    // Musica
    sf::Music music;

    // Historial para regresar
    std::stack<EventSnapshot> history;

    // Fade
    float fadeAlpha;
    bool fadingIn;

    // Hover
    int hoveredOption;
    int hoveredPause;  // 0=nada, 1=pausa, 2=regresar

    // Tiempo para animaciones
    sf::Clock clock;

public:
    Game();
    ~Game();
    void run();

private:
    bool loadFont();
    bool loadImage(const std::string& path);
    std::string getEventImagePath(int eventId) const;
    std::string getFinalImagePath() const;

    void handleInput();
    void update();
    void render();

    void renderCover();
    void renderInputScreen(const std::string& prompt, const std::string& subtitle = "");
    void renderGenderScreen();
    void displayEvent();
    void displayPauseMenu();
    void displayFinal();
    void displayCredits();
    void createOptionButtons(const Event& evt);
    void drawRoundedRect(sf::Vector2f pos, sf::Vector2f size,
                         sf::Color fill, sf::Color outline = sf::Color::Transparent,
                         float outlineThick = 0.f);
    void drawProgressBar();
    void drawTopBar();

    std::string replaceNames(const std::string& text) const;
    std::string wrapText(const std::string& text, unsigned int maxChars) const;
    std::string getRelationshipDescription() const;
    std::string getFinalText() const;

    void saveSnapshot();
    void restoreLastSnapshot();
};
