#pragma once
#include "../include/spaceship.h"
#include <SFML/Graphics/RenderWindow.hpp>

class control {
  spaceship &ship;
  sf::RenderWindow &window;

public:
  control(spaceship &, sf::RenderWindow &);
  control(control const &) = delete;
  void operator=(control const &) = delete;
  void update();
};
