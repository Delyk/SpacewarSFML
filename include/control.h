#pragma once
#include "../include/spaceship.h"

class control {
  spaceship &ship;

public:
  control(spaceship &);
  control(control const &) = delete;
  void operator=(control const &) = delete;
  void update();
};
