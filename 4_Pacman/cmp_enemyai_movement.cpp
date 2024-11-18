#include "cmp_enemyai_movement.h"
#include <SFML/Window/Keyboard.hpp>
#include "game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "LevelSystem.h"

EnemyAIMovementComponent::EnemyAIMovementComponent(Entity* p)
    : ActorMovementComponent(p), _state(ROAMING), _direction({ 1, 0 }){}

static const sf::Vector2i directions[] = { {1, 0}, {0, 1}, {0, -1}, {-1, 0} };

void EnemyAIMovementComponent::update(double dt) {
    std::cout << "move startt" << _state << std::endl;
    //amount to move
    const auto mva = (float)(dt * _speed);
    //Curent position
    const sf::Vector2f pos = _parent->getPosition();
    //Next position
    const sf::Vector2f newpos = pos + _direction * mva;
    //Inverse of our current direction
    const sf::Vector2i baddir = -1 * sf::Vector2i(_direction);
    //Random new direction
    sf::Vector2i newdir = directions[(rand() % 4)];

    switch (_state) {
    case ROAMING:
        // Check if the move is valid using validMove
        std::cout << "Checking move validity at position: " << validMove(newpos) << std::endl;
        if (!validMove(newpos)) {
            // If the move is invalid (i.e., there's a wall or obstruction), rotate
            _state = ROTATING;
        }
        else {
            // If the move is valid, continue moving
            move(_direction * mva);
        }
        break;
    case ROTATING: {
        sf::Vector2f checkPos = pos + sf::Vector2f(newdir.x, newdir.y) * mva;
        // Try to pick a new direction that doesn't reverse and doesn't hit a wall
        while (newdir == baddir || !validMove(checkPos)) {
            newdir = directions[(rand() % 4)];
            checkPos = pos + sf::Vector2f(newdir.x, newdir.y) * mva;  // Update checkPos
        }

        // Once a valid direction is chosen, apply it
        _direction = sf::Vector2f(newdir.x, newdir.y);
        _state = ROTATED;
        break;
    }


    case ROTATED:
        //have we left the waypoint?
        if (LevelSystem::getTileAt(pos) != LevelSystem::WAYPOINT) {
            _state = ROAMING; //yes
        }
        move(_direction * mva); //No
        break;
    }
    ActorMovementComponent::update(dt);

}
