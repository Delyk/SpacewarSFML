#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory_resource>
#include <vector>

unsigned randNum();
unsigned randDist(unsigned, unsigned);

class sky {
  sky(sf::RenderWindow &w) : window(w) { makeSky(); }
  sky(const sky &) = delete;
  sky &operator=(const sky &) = delete;
  sf::Vector2f getRandomPos() const;
  void makeSky();

  sf::RenderWindow &window;
  std::vector<sf::CircleShape> stars;
  constexpr static const unsigned stars_count = 10;
  constexpr static const unsigned star_size = 2;

public:
  static sky &instance(sf::RenderWindow &);
  void update();
};
