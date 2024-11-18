#include "cmp_player_movement.h"
#include <SFML/Window/Keyboard.hpp>
#include "game.h"
#include <iostream>

PlayerMovementComponent::PlayerMovementComponent(Entity* p)
    : ActorMovementComponent(p) {}

void PlayerMovementComponent::update(double dt) {
    // Only update if the entity is alive
    if (!_parent->isAlive()) {
        return;
    }

    const float moveSpeed = 200.f;  // Adjust speed
    sf::Vector2f direction(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction.x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction.x += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        direction.y -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        direction.y += 1.f;
    }

    // Normalize if necessary
    if (direction != sf::Vector2f(0.f, 0.f)) {
        direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y);
    }

    sf::Vector2f movement = direction * moveSpeed * static_cast<float>(dt);
    sf::Vector2f newPosition = _parent->getPosition() + movement;

    // Check if the new position is a valid move
    std::cout << "Checking move validity at position: " << validMove(newPosition) << std::endl;
    if (validMove(newPosition)) {
        // If valid, update the player's position
        move(movement);
    }

    ActorMovementComponent::update(dt);



}
