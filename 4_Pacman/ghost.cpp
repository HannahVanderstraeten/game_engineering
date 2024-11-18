/*#include "ghost.h" 
#include "game.h"
#include <cstdlib>  // For std::rand() and std::srand()
#include <ctime>    // For std::time()
#include "system_renderer.h"

using namespace sf;
using namespace std;

void Ghost::Update(double dt) {
    // Define movement speed (units per second)
    const float moveSpeed = 500.f;  // Adjust the speed as necessary

    // Get current position
    sf::Vector2f position = getPosition();

    // Random direction movement (no diagonal)
    float moveX = 0.f;
    float moveY = 0.f;

    // Randomly decide whether to move along the x-axis or y-axis
    int direction = std::rand() % 2;  // 0 for horizontal movement, 1 for vertical movement

    if (direction == 0) {
        // Move horizontally (left or right)
        moveX = (std::rand() % 3 - 1) * moveSpeed * dt * 3;  // Randomly choose -1, 0, or 1
    } else {
        // Move vertically (up or down)
        moveY = (std::rand() % 3 - 1) * moveSpeed * dt * 3;  // Randomly choose -1, 0, or 1
    }

    // Update position
    position.x += moveX;
    position.y += moveY;

    // Boundary checks to keep the ghost within the screen
    if (position.x < 0) position.x = 0;
    if (position.x > gameWidth) position.x = gameWidth;
    if (position.y < 0) position.y = 0;
    if (position.y > gameHeight) position.y = gameHeight;

    // Set the new position
    setPosition(position);

    Entity::Update(dt);
}*/

