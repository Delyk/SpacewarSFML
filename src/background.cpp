#include "../include/background.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdlib>
#include <random>

unsigned seed = static_cast<unsigned>(time(0));
const unsigned a = 1103515245;
const unsigned c = 12345;
const unsigned m = 2147483648;

unsigned randNum() {
  seed = (a * seed + c) % m;
  return seed;
}

unsigned randDist(unsigned lo, unsigned hi) { return lo + rand() % (hi - lo); }

float randDist(float lo, float hi) {
  return lo + static_cast<float>(rand()) / (m / (hi - lo));
}

sky &sky::instance(sf::RenderWindow &w) {
  static sky *instance = nullptr;
  if (!instance) {
    instance = new sky(w);
  }
  return *instance;
}

static float distance(sf::Vector2f a, sf::Vector2f b) {
  return std::hypot(a.x - b.x, a.y - b.y);
}

static bool isNeighbor(std::vector<sf::Vector2f> stars, sf::Vector2f p,
                       float minDist) {
  for (const auto &pt : stars) {
    if (distance(pt, p) < minDist)
      return true;
  }
  return false;
}

//Получить случайные координаты следующей звезды
sf::Vector2f sky::getRandomPos(sf::Vector2f pos) const { return {0, 0}; }

//Генерация неба
void sky::makeSky() {
  sf::Vector2u size = window.getSize();
  s.setRadius(star_size);
  s.setFillColor(sf::Color::White);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> x(0, size.x);
  std::uniform_real_distribution<float> y(0, size.y);
  int att = 0;
  stars_pos.emplace_back(x(gen), y(gen));
  s.setPosition(*stars_pos.begin());
  while (att < maxAtt && stars_pos.size() < stars_count) {
    sf::Vector2f candidate{x(gen), y(gen)};
    if (!isNeighbor(stars_pos, candidate, 5.0)) {
      stars_pos.push_back(candidate);
      att = 0;
    } else {
      att++;
    }
  }
  start = stars_pos.end();
}

//Анимация звёзд
void sky::update() {
  float time = clock.getElapsedTime().asSeconds();
  if (time >= update_time) {
    if (start != stars_pos.end()) {
      start++;
    } else {
      start = stars_pos.begin();
    }
    s.setPosition(*start);
    clock.restart();
  }
  window.draw(s);
}
