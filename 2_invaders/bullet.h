#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {
public:

  Bullet();
  Bullet(const sf::Vector2f& pos, const bool mode);

  void Update(const float &dt);
  //Render's all bullets (uses a similar trick to the ship renderer but on the bullet pool)
  static void Render(sf::RenderWindow& window);
  //Chose an inactive bullet and use it.
  static void Fire(const sf::Vector2f& pos, const bool mode);
  //Set all the bullets to -100, -100, set the spritesheet, set origin
  static void Init();

  ~Bullet()=default;
protected:

  void _Update(const float& dt);

  //false=player bullet, true=Enemy bullet
  bool _mode;
};