#include "../include/spaceship.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <iomanip>
#include <ios>
#include <iostream>

/*** Методы интерфейса для кораблей ***/
spaceship::spaceship(sf::RenderWindow &w) : window(w), state(*this) {
  init_body();
  a_inc = maxSpeed / 1000;
  a_dec = a_inc;
}

//Инициализация корпуса
void spaceship::init_body() {
  body.setPointCount(4);
  body.setPoint(0, sf::Vector2f(0.f, -8.f));
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
  engines = true;
  speedVect = body.getRotation();
  if (a < maxSpeed) {
    a += a_inc;
  }
}

void spaceship::stop() { engines = false; }

void spaceship::reverse() {
  if (a > -maxSpeed) {
    a -= a_dec;
  }
}

//Получить новые координаты объекта
inline float spaceship::getX() const {
  return a * std::cos((M_PI * (direction - 90)) / 180);
}

inline float spaceship::getY() const {
  return a * std::sin((M_PI * (direction - 90)) / 180);
}

//Движение объекта
void spaceship::update() {
  if (engines) {
    if (std::abs(direction - speedVect) < 20) {

    } else if (direction < speedVect) {
      direction += 0.1;
    } else if (direction > speedVect) {
      direction -= 0.1;
    }
  } else {
    if (speedVect != direction) {
      speedVect = direction;
    }
  }

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

  state.printState();
  window.draw(body);
}

//Вывод состояния корабля
spaceship::stat::stat(spaceship &ship) : parent(ship) {}

void spaceship::stat::printState() {
  float time = clock.getElapsedTime().asSeconds();
  if (time >= update_time) {
    system("clear");
    sf::Vector2f pos = parent.body.getPosition();
    std::cout << "X: " << std::fixed << std::setprecision(0) << pos.x
              << " Y: " << pos.y << std::endl;
    std::cout << "Engines: " << std::boolalpha << parent.engines << std::endl;
    std::cout << "Acceleration: " << parent.a << std::endl;
    std::cout << "Direction: " << parent.direction << std::endl;
    std::cout << "Vector: " << parent.speedVect << std::endl;
    std::cout << "Delta Vector: "
              << std::abs(parent.speedVect - parent.direction) << std::endl;
    clock.restart();
  }
}
