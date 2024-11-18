#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "game.h"
#include "bullet.h"

using namespace sf;
using namespace std;

sf::Texture spritesheet;
sf::Sprite invader;

// Assuming ships is defined globally
std::vector<Ship*> ships;
std::vector<Bullet*> bullets; // Declare globally
Player* player;

// Load function to initialize game assets
void Load() {
    if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
        return; // Exit if loading fails
    }

    // Assuming invaders_rows and invaders_columns are defined globally
    for (int r = 0; r < invaders_rows; ++r) {
        for (int c = 0; c < invaders_columns; ++c) {
            // Each invader uses a different part of the texture
            IntRect rect(Vector2i(32 * c, 0), Vector2i(32, 32));  // Adjust depending on the sprite sheet layout
            Vector2f position(100.f + c * 50.f, 100.f + r * 50.f);  // Adjust 50.f for spacing

            // Create a new Invader with the correct texture rect and position
            Invader* inv = new Invader(rect, position);
            ships.push_back(inv);  // Add to the ships vector
        }
    }

    // Create and add the player
    player = new Player();
    ships.push_back(player);
}

// Render function to draw the ships
void Render(RenderWindow& window) {
    for (const auto& s : ships) { // Use const auto& to avoid copying
        window.draw(*s);
    }
    Bullet::Render(window);

}

// Update function to update game state
void Update() {
    static Clock clock;
    float dt = clock.restart().asSeconds();

    player->Update(dt);

    for (auto& s : ships) {
        s->Update(dt);
        s->MoveDown(dt);  // Only invaders will move down, player ignores this
    }

    for (auto bullet : bullets) {
        bullet->Update(dt);  // Call _Update for each bullet
        
    }
}

int main() {
    // Create the game window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Space Invaders");

    // Load the sprites and create the invaders
    Load();
    Bullet::Init();

    // Main game loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        // Update the game state
        Update();

        // Clear the window, render the ships, and display them
        window.clear();
        Render(window);
        window.display();
    }

    // Clean up dynamically allocated ships
    for (auto& ship : ships) {
        delete ship; // Prevent memory leaks
    }
    ships.clear();

    for (auto& bullet : bullets) {
        delete bullet; // Prevent memory leaks
    }
    bullets.clear();

    return 0;
}
