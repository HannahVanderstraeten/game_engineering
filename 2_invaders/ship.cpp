//ship.cpp
#include "ship.h"
#include "game.h"
#include <iostream>
#include "bullet.h"
using namespace sf;
using namespace std;
bool Invader::direction;
float Invader::speed;



Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
  _sprite = ir;
  setTexture(spritesheet);
  setTextureRect(_sprite);
  _exploded = false;
};

void Ship::Update(const float &dt) {
    if (is_exploded()) {
        explosionTime -= dt; // Decrease the timer
        if (explosionTime <= 0.0f) {
            setPosition(-100, -100); // Move off-screen or set to invisible
            _exploded = false; // Reset the explosion state
            return; // Exit early
        }

        // Calculate the fade-out effect based on remaining time
        opacity = 255.0f * (explosionTime / explosionDuration); // Linear fade-out
        setColor(Color(255, 255, 255, static_cast<Uint8>(opacity))); // Set sprite color with new opacity
    }

}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;
Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
    setOrigin(Vector2f(16.f, 16.f));;
    setPosition(pos);
}

void Invader::Update(const float& dt) {
    Ship::Update(dt);
    static float firetime = 0.0f;
    firetime -= dt;
    move(Vector2f(dt * (direction ? 1.0f : -1.0f) * speed, 0.0f));

    if ((direction && getPosition().x > gameWidth - 16) ||
        (!direction && getPosition().x < 16)) {
        direction = !direction;
        for (int i = 0; i < ships.size(); ++i) {
            ships[i]->move(Vector2f(0.0f, 24.0f));
        }
    }

    if (firetime <= 0 && rand() % 100 == 0) {
        Bullet::Fire(getPosition(), true);
        firetime = 4.0f + (rand() % 60);
    }
}

// Constructor
Player::Player() : Ship(IntRect(Vector2i(160, 32), Vector2i(32, 32))) {
    // Set initial position at the middle-bottom of the screen
    setPosition({ gameWidth * .5f, gameHeight - 32.f });
}

// Update function
void Player::Update(const float& dt) {
    Ship::Update(dt);  // Call the parent class's Update function (if necessary)
    static float firetime = 0.0f;
    firetime -= dt;
    // Define movement speed (units per second)
    const float moveSpeed = 200.f;  // Adjust the speed as necessary

    // Get current position
    sf::Vector2f position = getPosition();

    // Move left (using Left arrow key)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        position.x -= moveSpeed * dt;
        if (position.x < 0)  // Prevent moving off the left edge of the screen
            position.x = 0;
    }

    // Move right (using Right arrow key)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        position.x += moveSpeed * dt;
        if (position.x + getGlobalBounds().width > gameWidth)  // Prevent moving off the right edge of the screen
            position.x = gameWidth - getGlobalBounds().width;
    }

    // Set the new position
    setPosition(position);

    
    // Fire bullet only if cooldown has expired
    if (firetime <= 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        Bullet::Fire(getPosition(), false); // Fire a bullet
        firetime = 0.7f; // Reset cooldown timer
    }

    for (auto& bullet : bullets) {
        bullet->Update(dt);
    }
}


bool Ship::is_exploded() const {
    return _exploded; // Return the current state of _exploded
}


void Ship::Explode() {
    setTextureRect(IntRect(Vector2i(128, 32), Vector2i(32, 32)));
    _exploded = true;
    explosionTime = explosionDuration; // Set the timer to the defined duration
    opacity = 255.0f; // Start fully opaque
}