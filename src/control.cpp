#include "../include/control.h"
#include "../include/spaceship.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

/*** Методы класса для управления кораблём ***/
//Конструктор
control::control(spaceship &ship, sf::RenderWindow &w)
    : ship(ship), window(w) {}

//Функция обновления
void control::update(sf::Event &e) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    ship.rotateLeft();
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    ship.rotateRight();
  }

  if (e.type == sf::Event::KeyReleased) {
    if ((e.key.code == sf::Keyboard::W) || (e.key.code == sf::Keyboard::S)) {
      ship.stop();
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    ship.boost();
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    ship.reverse();
  }
}
