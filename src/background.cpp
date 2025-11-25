#include "../include/background.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

unsigned seed = static_cast<unsigned>(time(0));
const unsigned a = 1103515245;
const unsigned c = 12345;
const unsigned m = 2147483648;

unsigned randNum() {
  seed = (a * seed + c) % m;
  return seed;
}

unsigned randDist(unsigned lo, unsigned hi) { return lo + rand() % (hi - lo); }

sky &sky::instance(sf::RenderWindow &w) {
  static sky *instance = nullptr;
  if (!instance) {
    instance = new sky(w);
  }
  return *instance;
}

//Получить случайные координаты следующей звезды
sf::Vector2f sky::getRandomPos() const {
  sf::Vector2u size = window.getSize();
  return {static_cast<float>(randDist(0, size.x)),
          static_cast<float>(randDist(0, size.y))};
}

//Генерация неба
void sky::makeSky() {
  for (unsigned i = 0; i < stars_count; i++) {
    sf::Vector2f pos = getRandomPos();
    sf::CircleShape s(star_size);
    s.setPosition(pos);
    s.setFillColor(sf::Color::White);
    stars.push_back(s);
  }
}

//Анимация звёзд
void sky::update() {
  for (auto i : stars) {
    window.draw(i);
  }
}
