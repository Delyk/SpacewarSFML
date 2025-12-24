#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

class spaceship {
  constexpr static const sf::Angle rotateSpeed = sf::degrees(5);
  constexpr static const float maxSpeed = 0.5;

public:
  enum spaceship_state { boosted, stoped, left, right };

protected:
  sf::ConvexShape body;
  sf::RenderWindow &window;
  sf::Clock clock;
  float update_time = 0.2;
  sf::Angle direction;
  float angle_speed = 0.2;

  void init_body();
  void printState();
  void turning();
  inline float getX(float, sf::Angle);
  inline float getY(float, sf::Angle);
  spaceship_state state;

public:
  spaceship(sf::RenderWindow &);
  void rotateLeft();
  void rotateRight();
  void boost(bool reverse = false);
  void stop();
  void setState(spaceship_state);
  void update();
};
