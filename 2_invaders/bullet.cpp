#include "bullet.h"
#include "game.h"
#include "ship.h"
#include <iostream>
#include <vector> // Make sure to include this for std::vector

using namespace sf;
using namespace std;


   // Vector to hold bullet pointers

// Default constructor
Bullet::Bullet() {
    setPosition(-100, -100);  // Set to off-screen by default
}

// Parameterized constructor
Bullet::Bullet(const sf::Vector2f& pos, const bool mode) : Sprite() {
    setTexture(spritesheet);  // Ensure spritesheet is loaded before this
    _mode = mode;  // Set the bullet's direction mode
    setPosition(pos);  // Set the position of the bullet

    // Set the texture rectangle for the bullet
    if (!_mode) {
        // Player's bullet
        setTextureRect(IntRect(32, 32, 32, 32)); // Adjust according to your spritesheet
    }
    else {
        setTextureRect(IntRect(64, 32, 32, 32)); // Enemy bullet texture
    }
}

void Bullet::Update(const float& dt) {
    for (auto bullet : bullets) { // Iterate over bullet pointers
        if (bullet) {
            bullet->_Update(dt); // Call _Update for each bullet in the vector
        }
    }
}

void Bullet::_Update(const float& dt) {
    // Check if bullet is off-screen
    if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
        setPosition(-100, -100);  // Set to off-screen
        return;  // Bullet is off-screen
    }


    // Move the bullet based on its mode
    move(Vector2f(0, dt * 200.0f * (_mode ? 1.0f : -1.0f)));  // Upwards or downwards
    const FloatRect boundingBox = getGlobalBounds();

    for (auto s : ships) {
        if (!_mode && s == player) {
            continue;  // Player bullets don't collide with the player
        }
        if (_mode && s != player) {
            continue;  // Invader bullets don't collide with other invaders
        }
        if (!s->is_exploded() && s->getGlobalBounds().intersects(boundingBox)) {
            s->Explode();  // Explode the ship
            setPosition(Vector2f(-100, -100));  // Move bullet off-screen
            return;
        }
    }
}

void Bullet::Init() {
    bullets.reserve(256); // Reserve space for bullets to avoid reallocations
}

void Bullet::Fire(const sf::Vector2f& pos, const bool mode) {
    Bullet* newBullet = new Bullet(pos, mode); // Create a new bullet
    bullets.push_back(newBullet); // Add to the vector
}

void Bullet::Render(sf::RenderWindow& window) {
    for (auto bullet : bullets) { // Iterate over bullet pointers
        if (bullet && bullet->getPosition().y >= 0) { // Only render active bullets
            window.draw(*bullet); // Dereference the pointer to draw
        }
    }
}



