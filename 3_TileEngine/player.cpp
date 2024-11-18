#include "player.h"
#include "game.h"
#include <cmath>  // For sqrt function
#include "LevelSystem.h"

using namespace sf;
using namespace std;

void Player::Update(double dt) {
    // Define movement speed (units per second)
    const float moveSpeed = 200.f;  // Adjust the speed as necessary

    // Get current position
    sf::Vector2f position = getPosition();

    // Track movement direction
    float moveX = 0.f;
    float moveY = 0.f;

    // Move left (using Left arrow key)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        moveX -= moveSpeed * dt;
    }

    // Move right (using Right arrow key)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        moveX += moveSpeed * dt;
    }

    // Move up (using Up arrow key)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        moveY -= moveSpeed * dt;
    }

    // Move down (using Down arrow key)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        moveY += moveSpeed * dt;
    }

    // Normalize diagonal movement speed
    if (moveX != 0 && moveY != 0) {
        float diagonalSpeedFactor = std::sqrt(2.f);  // Scale speed by sqrt(2) for diagonal movement
        moveX /= diagonalSpeedFactor;
        moveY /= diagonalSpeedFactor;
    }

    // Update position
    position.x += moveX;
    position.y += moveY;

    // Boundary checks to keep player within the screen
    if (position.x < 0) position.x = 0;
    if (position.x > gameWidth) position.x = gameWidth;
    if (position.y < 0) position.y = 0;
    if (position.y > gameHeight) position.y = gameHeight;

    // Set the new position
    setPosition(position);

    Entity::Update(dt);
}

Player::Player()
    : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
    _shape->setFillColor(Color::Magenta);
    _shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::Render(sf::RenderWindow& window) const {
    window.draw(*_shape);
}

bool Player::validmove(Vector2f pos) {
  return (ls::getTileAt(pos) != ls::WALL);
}
