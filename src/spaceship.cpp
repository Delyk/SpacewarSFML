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

/*
1. Обработка ввода:
   - Если поворот лево: angular_velocity -= 0.2
   - Если поворот право: angular_velocity += 0.2
   - Иначе: angular_velocity *= 0.9 (затухание, опционально)
   - angle += angular_velocity
   - angle = modulo(angle, 2π)  // нормализация [-π, π]

2. Ускорение (если thrust):
   - accel = 0.1 * dt  // tunable, dt — delta time
   - ax = accel * cos(angle)
   - ay = accel * sin(angle)
   - vx += ax
   - vy += ay
   - Ограничьте скорость: if sqrt(vx² + vy²) > 0.5, нормализуйте и умножьте на
0.5

3. Обновление позиции:
   - x += vx * dt
   - y += vy * dt
   - Wrap-around: x = modulo(x, 640); y = modulo(y, 360)

 */

/*** Методы интерфейса для кораблей ***/
spaceship::spaceship(sf::RenderWindow &w) : window(w) { init_body(); }

//Инициализация корпуса
void spaceship::init_body() {
  body.setPointCount(4);
  body.setPoint(0, sf::Vector2f(0.f, -8.f));
  body.setPoint(1, sf::Vector2f(-5.f, 5.f));
  body.setPoint(2, sf::Vector2f(0.f, 3.f));
  body.setPoint(3, sf::Vector2f(5.f, 5.f));

  body.setFillColor(sf::Color::Black);
  body.setOutlineColor(sf::Color::White);
  body.setOutlineThickness(1.5f);

  body.setOrigin({0.f, 0.f});
  sf::Vector2u center = window.getSize();
  body.setPosition({center.x / 2.f, center.y / 2.f});
  this->direction = body.getRotation();
}

//Вращение корабля
void spaceship::rotateLeft() { body.rotate(-rotateSpeed); }

void spaceship::rotateRight() { body.rotate(rotateSpeed); }

//Двигатели
void spaceship::boost(bool reverse) {}

void spaceship::stop() { state = stoped; }

//Получить новые координаты объекта
inline float spaceship::getX(float a, sf::Angle dir) {
  return a * std::cos(dir.asRadians());
}

inline float spaceship::getY(float a, sf::Angle dir) {
  return a * std::sin(dir.asRadians());
}

//Найти кратчайший угол поворота
void spaceship::turning() {}

//Состояние корабля
void spaceship::setState(spaceship_state st) { state = st; }

//Движение объекта
void spaceship::update() {
  switch (state) {
  case boosted:
    break;
  case stoped:
    break;
  case left:
    rotateLeft();
    break;
  case right:
    rotateRight();
    break;
  }

  // sf::Vector2f offset{x, y};
  // body.move(offset);

  // printState();
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
    case stoped:
      std::cout << "stoped";
      break;
    case left:
      std::cout << "left";
      break;
    case right:
      std::cout << "right";
      break;
    }
    std::cout << std::endl;
    // std::cout << "Acceleration: " << std::setprecision(4) << a_inc <<
    // std::endl; std::cout << "Speed: " << a << std::endl;
    std::cout << std::setprecision(0)
              << "Rotation: " << body.getRotation().asDegrees() << std::endl;
    std::cout << "Direction: " << direction.asDegrees() << std::endl;
    clock.restart();
  }
}
