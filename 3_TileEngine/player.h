//player.h
#pragma once
#include "entity.h"
#include <SFML/System.hpp> 

class Player : public Entity {
 private:
  float _speed;

 public:
  void Update(double dt) override;
  Player();
  void Render(sf::RenderWindow &window) const override;
  bool validmove(sf::Vector2f pos);
};