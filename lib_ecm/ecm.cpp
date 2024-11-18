//ecm.cpp
#include "ecm.h"
#include <SFML/Graphics/Shape.hpp>
#include <iostream>

using namespace std;
using namespace sf;

// Define Entity constructor with initial values
Entity::Entity() : _position(0, 0), _rotation(0), _alive(true), _visible(true), _fordeletion(false) {}

// Destructor
Entity::~Entity() {}

// Getter for position
const Vector2f& Entity::getPosition() const {
    return _position;
}

// Setter for position
void Entity::setPosition(const Vector2f& pos) {
    _position = pos;
}

// Getter for rotation
float Entity::getRotation() const {
    return _rotation;
}

// Setter for rotation
void Entity::setRotation(float rotation) {
    _rotation = rotation;
}

// Getter for alive status
bool Entity::isAlive() const {
    return _alive;
}

// Setter for alive status
void Entity::setAlive(bool alive) {
    _alive = alive;
}

// Set entity to be deleted
void Entity::setForDelete() {
    _fordeletion = true;
}

// Check if entity is marked for deletion
bool Entity::is_fordeletion() const {
    return _fordeletion;
}

// Check if entity is visible
bool Entity::isVisible() const {
    return _visible;
}

// Setter for visibility
void Entity::setVisible(bool visible) {
    _visible = visible;
}

// Update function that calls update on each component
void Entity::update(double dt) {
    if (_components.empty()) {
        std::cout << "No components to update!" << std::endl;
    }
    for (const auto& component : _components) {
        if (component) {
            component->update(dt);
        }
        else {
            std::cout << "Null component found!" << std::endl;
        }
    }
}


// Render function that checks visibility and renders each component
void Entity::render() {
    if (_visible) {  // Check if the entity is visible
        for (const auto& component : _components) {
            component->render();  // Render each component
        }
    }
}

// Component constructor that initializes the _parent and sets _fordeletion to false
Component::Component(Entity* const p) : _parent(p), _fordeletion(false) {}

// Destructor
Component::~Component() {}

// Check if the component is marked for deletion
bool Component::is_fordeletion() const {
    return _fordeletion;
}
