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
#include <iomanip>
#include <ios>
#include <iostream>

/*** Методы интерфейса для кораблей ***/
spaceship::spaceship(sf::RenderWindow &w) : window(w) { init_body(); }

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
  engines = true;
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

//Найти кратчайший угол поворота
void spaceship::turning() {
  int path = std::min(std::abs(direction - speedVect),
                      360 - std::abs(direction - speedVect));
  int len = std::abs(direction - speedVect);
  if (path < len) {
    if (direction < 0) {
      direction = 360;
    } else if (direction > 360) {
      direction = 0;
    }

    if (direction < speedVect) {
      direction -= angle_speed;
    } else if (direction > speedVect) {
      direction += angle_speed;
    }
  } else {
    if (direction < speedVect) {
      direction += angle_speed;
    } else if (direction > speedVect) {
      direction -= angle_speed;
    }
  }
}

//Движение объекта
void spaceship::update() {
  if (engines) {
    if (direction != speedVect) {
      turning();
    }
  } else {
    if (speedVect != direction) {
      a_inc = std::abs(a_inc);
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

  printState();
  window.draw(body);
}

//Вывод состояния корабля

void spaceship::printState() {
  float time = clock.getElapsedTime().asSeconds();
  if (time >= update_time) {
    system("clear");
    sf::Vector2f pos = body.getPosition();
    std::cout << "X: " << std::fixed << std::setprecision(0) << pos.x
              << " Y: " << pos.y << std::endl;
    std::cout << "Engines: " << std::boolalpha << engines << std::endl;
    std::cout << "Acceleration: " << std::setprecision(4) << a_inc << std::endl;
    std::cout << "Speed: " << a << std::endl;
    std::cout << std::setprecision(0) << "Rotation: " << body.getRotation()
              << std::endl;
    std::cout << "Direction: " << direction << std::endl;
    std::cout << "Speed Vector: " << speedVect << std::endl;
    clock.restart();
  }
}
