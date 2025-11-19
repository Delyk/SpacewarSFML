#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

class spaceship {
  constexpr static const float rotateSpeed = 1.f;
  constexpr static const float maxSpeed = 0.5;

protected:
  class stat {
    spaceship &parent;
    sf::Clock clock;
    float update_time = 0.1;

  public:
    stat(spaceship &);
    void printState();
  };

  sf::ConvexShape body;
  sf::RenderWindow &window;
  stat state;
  float a = 0.f;
  float a_inc;
  float a_dec;
  float direction = 0.f;
  int speedVect = 0;
  bool engines = false;

  void init_body();
  inline float getX() const;
  inline float getY() const;

public:
  spaceship(sf::RenderWindow &);
  void rotateLeft();
  void rotateRight();
  void boost();
  void stop();
  void reverse();
  void update();
};
