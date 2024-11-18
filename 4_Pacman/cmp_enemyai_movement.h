//"cmp_enemyAI_movement.h"
#pragma once

#include "cmp_actor_movement.h"
#include <SFML/Window/Keyboard.hpp> // For handling keyboard input


class EnemyAIMovementComponent : public ActorMovementComponent {
protected:
    sf::Vector2f _direction;
    enum state { ROAMING, ROTATING, ROTATED };
    state _state;
public:
    explicit EnemyAIMovementComponent(Entity* p);
    void update(double dt) override;
};
