#include "../include/spaceship.h"
#include "../include/settings.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

/*** Методы интерфейса для кораблей ***/
spaceship::spaceship(sf::RenderWindow &w) : window(w) { init_body(); }

//Инициализация корпуса
void spaceship::init_body() {
  body.setPointCount(4);
  body.setPoint(0, sf::Vector2f(0.f, -10.f));
  body.setPoint(1, sf::Vector2f(-5.f, 5.f));
  body.setPoint(2, sf::Vector2f(0.f, 3.f));
  body.setPoint(3, sf::Vector2f(5.f, 5.f));

  body.setFillColor(sf::Color::Transparent);
  body.setOutlineColor(sf::Color::White);
  body.setOutlineThickness(1.5f);

  body.setOrigin(0.f, 0.f);
  sf::Vector2u center = window.getSize();
  body.setPosition(center.x / 2.f, center.y / 2.f);
}

//Вращение корабля
void spaceship::rotateLeft() { body.rotate(-rotateSpeed); }

void spaceship::rotateRight() { body.rotate(rotateSpeed); }

//Двигатели
void spaceship::boost() {
  direction = body.getRotation();
  if (a < maxSpeed) {
    a += 0.01;
  }
}

void spaceship::reverse() {
  if (a > -maxSpeed) {
    a -= 0.01;
  }
}

//Получить новые координаты объекта
inline float spaceship::getX() const {
  return a * std::cos((M_PI * (direction - 90)) / 180);
}

inline float spaceship::getY() const {
  return a * std::sin((M_PI * (direction - 90)) / 180);
}

//Обновление объекта
void spaceship::update() {
  if (a) {
    sf::Vector2f offset{getX(), getY()};
    body.move(offset);
    sf::Vector2f pos = body.getPosition();
    sf::Vector2u size = window.getSize();

    if (pos.x < 0) {
      pos.x = size.x;
    } else if (pos.x > size.x) {
      pos.x = 0;
    }

    if (pos.y < 0) {
      pos.y = size.y;
    } else if (pos.y > size.y) {
      pos.y = 0;
    }

    if (pos != body.getPosition()) {
      body.setPosition(pos);
    }
  }

  window.draw(body);
}
