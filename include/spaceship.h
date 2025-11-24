#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

class spaceship {
  constexpr static const float rotateSpeed = 0.5;
  constexpr static const float maxSpeed = 0.5;

protected:
  sf::ConvexShape body;
  sf::RenderWindow &window;
  sf::Clock clock;
  float update_time = 0.1;
  float a = 0.f;
  float a_inc = maxSpeed / 1000;
  float direction = 0.f;
  float angle_speed = 0.2;
  int speedVect = 0;
  int path = 0;
  bool engines = false;

  void init_body();
  void printState();
  void turning();
  inline float getX(float, int);
  inline float getY(float, int);

public:
  spaceship(sf::RenderWindow &);
  void rotateLeft();
  void rotateRight();
  void boost(bool reverse = false);
  void stop();
  void update();
};
