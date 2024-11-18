#include <SFML/Graphics.hpp>
#include "player.h"
#include "entity.h"
#include "game.h"
#include "LevelSystem.h"


using namespace sf;
using namespace std;


std::unique_ptr<Player> player;

Font font;
Text text;

void Load() {
    ls::loadLevelFile("res/levels/maze.txt");
    player = std::make_unique<Player>();

    // Iterate over the tiles to find the START tile
    for (size_t y = 0; y < ls::getHeight(); ++y) {
        for (size_t x = 0; x < ls::getWidth(); ++x) {
            if (ls::getTile({ x, y }) == ls::START) {
                // Set player position to the center of the START tile
                sf::Vector2f startTilePosition = ls::getTilePosition({ x, y });
                // Adjust for the circle's radius
                startTilePosition.x += 25.f;  // Offset by radius
                startTilePosition.y += 25.f;  // Offset by radius
                player->setPosition(startTilePosition);
                break;
            }
        }
    }


    // Print the level to the console
    for (size_t y = 0; y < ls::getHeight(); ++y) {
        for (size_t x = 0; x < ls::getWidth(); ++x) {
            cout << ls::getTile({ x, y });
        }
        cout << endl;
    }



}

void Update(RenderWindow& window) {
    // Reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();
    // check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }

    player->Update(dt);


    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }

}

void Render(RenderWindow& window) {
    player->Render(window);
    ls::Render(window);
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "Tile Engine");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}