//ship.h
#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
protected:
    sf::IntRect _sprite;
    //Default constructor is hidden
    Ship();

    bool _exploded = false;
    float explosionTime = 0.0f;      // Timer for the explosion
    const float explosionDuration = 2.0f; // Duration the explosion should last
    float opacity = 255.0f;

public:
    //Constructor that takes a sprite
    explicit Ship(sf::IntRect ir);
    //Pure virtual deconstructor -- makes this an abstract class and avoids undefined behaviour!
    virtual ~Ship() = 0;
    //Update, virtual so can be overridden, but not pure virtual
    virtual void Update(const float &dt);

    virtual void MoveDown(float dt) {}

    bool is_exploded() const;
    virtual void Explode();
};

class Invader : public Ship {
public:
    static bool direction;
    static float speed;
    Invader(sf::IntRect ir, sf::Vector2f pos);
    Invader();
    void Update(const float &dt) override;
    void MoveDown(float dt) override {
        move(0, 24 * dt);  // Move the invader down
    }
};

class Player : public Ship {
public:
  Player();
  void Update(const float &dt) override;
};