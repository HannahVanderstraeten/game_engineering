// cmp_player_movement.h
#pragma once

#include "cmp_actor_movement.h"
#include <SFML/Window/Keyboard.hpp> // For handling keyboard input

class PlayerMovementComponent : public ActorMovementComponent {
public:
    explicit PlayerMovementComponent(Entity* p);
    void update(double dt) override;
};
