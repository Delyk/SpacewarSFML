#include "../include/control.h"
#include "../include/settings.h"
#include "../include/spaceship.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

extern class clock globalTimer;

/*** Методы класса для управления кораблём ***/
//Конструктор
control::control(spaceship &ship, sf::RenderWindow &w)
    : ship(ship), window(w) {}

//Функция обновления
void control::update() {

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    ship.rotateLeft();
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    ship.rotateRight();
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    ship.boost();
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    ship.reverse();
  }
}
