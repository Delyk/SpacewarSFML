#include "../include/spaceship.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Window/Keyboard.hpp>

/*** Методы интерфейса для кораблей ***/
spaceship::spaceship(sf::RenderWindow &w) : window(w) {}

//Геттер/сеттер координат корабля
void spaceship::setPos(sf::Vector2f pos) {
  this->pos = pos;
  body.setPosition(this->pos);
}

sf::Vector2f spaceship::getPos() const { return pos; }

/*** Стандартный корабль ***/
//Конструктор с созданием формы
standart_ship::standart_ship(sf::RenderWindow &w) : spaceship(w) {
  body.setPointCount(3);
  body.setPoint(0, sf::Vector2f(0.f, -10.f));
  body.setPoint(1, sf::Vector2f(-5.f, 5.f));
  body.setPoint(2, sf::Vector2f(5.f, 5.f));

  body.setFillColor(sf::Color::Transparent);
  body.setOutlineColor(sf::Color::White);
  body.setOutlineThickness(1.5f);

  body.setOrigin(0.f, 0.f);
  sf::Vector2u center = window.getSize();
  body.setPosition(center.x / 2.f, center.y / 2.f);
}

//Обновление объекта
void standart_ship::update() { window.draw(body); }
