// pacman.h
#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "scene.h"

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

class MenuScene : public Scene {
private:
    sf::Text text;
    sf::Font font; // Add a font member for text rendering

public:
    MenuScene() = default;

    void update(double dt) override;
    void render() override; 
    void load() override;
};

class GameScene : public Scene {
private:
    sf::Text text;
    sf::Font font;
    sf::Clock scoreClock;

    void respawn(); // Define respawn logic

public:
    GameScene() = default;

    void update(double dt) override;
    void render() override; 
    void load() override;
};
