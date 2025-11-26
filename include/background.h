#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory_resource>
#include <vector>

unsigned randNum();
unsigned randDist(unsigned, unsigned);
float randDist(float, float);

class sky {
  sky(sf::RenderWindow &w) : window(w) { makeSky(); }
  sky(const sky &) = delete;
  sky &operator=(const sky &) = delete;
  sf::Vector2f getRandomPos(sf::Vector2f) const;
  void makeSky();

  sf::RenderWindow &window;
  std::vector<sf::CircleShape> stars;
  std::vector<sf::Vector2f> stars_pos;
  constexpr static const unsigned stars_count = 10;
  constexpr static const unsigned star_size = 2;
  unsigned star_radius = 50;
  const int maxAtt = stars_count;
  sf::Clock clock;
  float update_time = 0.1;
  sf::CircleShape s;
  std::vector<sf::Vector2f>::iterator start;

public:
  static sky &instance(sf::RenderWindow &);
  void update();
};
