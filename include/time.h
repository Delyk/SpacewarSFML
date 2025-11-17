#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

class clock {
  sf::Clock clk;
  float time;

public:
  clock();

  void update();
  float getTime();
};
