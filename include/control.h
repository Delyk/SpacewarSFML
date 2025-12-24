#pragma once
#include "../include/spaceship.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <optional>

class control {
  spaceship &ship;
  sf::RenderWindow &window;
  enum prev_state { PRESS, RELEASE } state;

  control(spaceship &, sf::RenderWindow &);
  control(control const &) = delete;
  void operator=(control const &) = delete;

public:
  static control &instance(spaceship &, sf::RenderWindow &);
  void update(const std::optional<sf::Event> &);
};
