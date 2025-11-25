#pragma once
#include "../include/spaceship.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class control {
  spaceship &ship;
  sf::RenderWindow &window;

  control(spaceship &, sf::RenderWindow &);
  control(control const &) = delete;
  void operator=(control const &) = delete;

public:
  static control &instance(spaceship &, sf::RenderWindow &);
  void update(sf::Event &);
};
