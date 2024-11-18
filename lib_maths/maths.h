#pragma once

#include <SFML/System.hpp>
#include <cmath>
#include <iostream>
#include <vector>

namespace sf {
  // Create a definition for a sf::vector using size_t types
  typedef Vector2<size_t> Vector2ul;

  // Returns the length (magnitude) of an sf::Vector
  template <typename T>
  double length(const Vector2<T> &v) {
    return std::sqrt(v.x * v.x + v.y * v.y);  // Pythagorean theorem for 2D vector magnitude
  }

  // Return normalized sf::Vector (a vector with length 1)
  template <typename T>
  Vector2<T> normalize(const Vector2<T> &v) {
    Vector2<T> vector;
    double l = length(v);  // Get the length of the vector
    if (l != 0) {
      vector.x = static_cast<T>(v.x / l);
      vector.y = static_cast<T>(v.y / l);
    }
    return vector;
  }

  // Allow casting from one sf::Vector internal type to another
  template <typename T, typename U>
  Vector2<T> Vcast(const Vector2<U> &v) {
    return Vector2<T>(static_cast<T>(v.x), static_cast<T>(v.y));
  }

  // Degrees to radians conversion
  static double deg2rad(double degrees) {
    return degrees * (3.14159265358979323846 / 180.0);  // Convert degrees to radians
  }

  // Rotate an sf::Vector by an angle (degrees)
  template <typename T>
  Vector2<T> rotate(const Vector2<T> &v, const double degrees) {
    const double theta = deg2rad(degrees);  // Convert degrees to radians
    const double cs = std::cos(theta);      // Cosine of the angle
    const double sn = std::sin(theta);      // Sine of the angle
    return Vector2<T>(
      static_cast<T>(v.x * cs - v.y * sn),  // Rotate using 2D rotation matrix
      static_cast<T>(v.x * sn + v.y * cs)
    );
  }

  // Allow sf::Vector to be output to a stream (for debugging or logging)
  template <typename T>
  std::ostream &operator<<(std::ostream &os, const Vector2<T> &v) {
    os << '(' << v.x << ',' << v.y << ')';
    return os;
  }
}
