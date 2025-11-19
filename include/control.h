#pragma once
#include "../include/spaceship.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class control {
  spaceship &ship;
  sf::RenderWindow &window;

public:
  control(spaceship &, sf::RenderWindow &);
  control(control const &) = delete;
  void operator=(control const &) = delete;
  void update(sf::Event &);
};
