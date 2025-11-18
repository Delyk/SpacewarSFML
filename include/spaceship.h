#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

class spaceship {
  constexpr static const float rotateSpeed = 1.f;
  constexpr static const float maxSpeed = 1.f;
  float a = 0.f;
  int direction = 0;

protected:
  sf::ConvexShape body;
  sf::RenderWindow &window;

  void init_body();
  inline float getX() const;
  inline float getY() const;

public:
  spaceship(sf::RenderWindow &);
  void rotateLeft();
  void rotateRight();
  void boost();
  void reverse();
  void update();
};
