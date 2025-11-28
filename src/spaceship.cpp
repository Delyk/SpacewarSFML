#include "../include/spaceship.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
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
void spaceship::boost(bool reverse) {
  speedVect = body.getRotation();
  if (reverse) {
    if (prev_state == boosted) {
      changes = true;
    }
    state = reversed;
    if (a > -maxSpeed) {
      a -= a_inc;
    }
  } else {
    if (prev_state == reversed) {
      changes = true;
    }
    state = boosted;
    if (a < maxSpeed) {
      a += a_inc;
    }
  }
}

void spaceship::stop() {
  if (state != stoped) {
    prev_state = state;
  }
  state = stoped;
}

//Получить новые координаты объекта
inline float spaceship::getX(float a, int dir) {
  return a * std::cos((M_PI * (dir - 90)) / 180);
}

inline float spaceship::getY(float a, int dir) {
  return a * std::sin((M_PI * (dir - 90)) / 180);
}

//Найти кратчайший угол поворота
void spaceship::turning() {
  int len = std::abs(direction - speedVect);
  path = std::min(len, 360 - len);
  bool revDir = std::abs(180 - path) < 40;
  if (!revDir && changes && path) {

    if (a < 0) {
      a = std::abs(a);

    } else {
      a = -a;
    }
    prev_state = state;
    changes = false;
  } else if (revDir) {
    a = -a;
    direction = speedVect;
  } else if (path < len) {
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
  if (direction != speedVect) {
    switch (state) {
    case boosted:
    case reversed:
      turning();
      break;
    case stoped:
      speedVect = direction;
      break;
    }
  }

  float x = getX(a, direction), y = getY(a, direction);
  sf::Vector2f offset = {x, y};
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
    std::cout << "State: ";
    switch (state) {
    case boosted:
      std::cout << "boost";
      break;
    case reversed:
      std::cout << "reverse";
      break;
    case stoped:
      std::cout << "stoped";
      break;
    }
    std::cout << " Prev state: ";
    switch (prev_state) {
    case boosted:
      std::cout << "boost";
      break;
    case reversed:
      std::cout << "reverse";
      break;
    case stoped:
      std::cout << "stoped";
      break;
    }

    std::cout << std::endl;
    std::cout << "Acceleration: " << std::setprecision(4) << a_inc << std::endl;
    std::cout << "Speed: " << a << std::endl;
    std::cout << std::setprecision(0) << "Rotation: " << body.getRotation()
              << std::endl;
    std::cout << "Direction: " << direction << std::endl;
    std::cout << "Speed Vector: " << speedVect << std::endl;
    std::cout << "Path: " << path << std::endl;
    clock.restart();
  }
}
