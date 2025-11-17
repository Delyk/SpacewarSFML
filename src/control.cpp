#include "../include/control.h"
#include "../include/settings.h"
#include "../include/spaceship.h"
#include "../include/time.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

extern class clock globalTimer;

/*** Методы класса для управления кораблём ***/
//Конструктор
control::control(spaceship &ship) : ship(ship) {}

//Функция обновления
void control::update() {
  sf::Vector2f new_pos = ship.getPos();
  float time = globalTimer.getTime();

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    new_pos.x -= SHIP_SPEED * time;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    new_pos.x += SHIP_SPEED * time;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    new_pos.y -= SHIP_SPEED * time;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    new_pos.y += SHIP_SPEED * time;
  }

  if (new_pos != ship.getPos()) {
    ship.setPos(new_pos);
  }
}
