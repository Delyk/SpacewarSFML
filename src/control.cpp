#include "../include/control.h"
#include "../include/spaceship.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <optional>

/*** Методы класса для управления кораблём ***/
//Конструктор
control::control(spaceship &ship, sf::RenderWindow &w)
    : ship(ship), window(w) {}

///Получить класс
control &control::instance(spaceship &ship, sf::RenderWindow &w) {
  static control *instance = nullptr;
  if (!instance) {
    instance = new control(ship, w);
  }
  return *instance;
}

//Функция обновления
void control::update(const std::optional<sf::Event> &e) {
  const sf::Event::KeyPressed *press = e->getIf<sf::Event::KeyPressed>();
  const sf::Event::KeyReleased *release = e->getIf<sf::Event::KeyReleased>();

  if (press && release) {
    std::cout << "BOTH" << std::endl;
  } else if (press) {
    std::cout << "PRESS" << std::endl;
  } else if (release) {
    std::cout << "RELEASE" << std::endl;
  } else {
    std::cout << "NONE" << std::endl;
  }
  if (press) {
    switch (press->code) {
    case sf::Keyboard::Key::A:
      ship.setState(spaceship::left);
      break;
    case sf::Keyboard::Key::D:
      ship.setState(spaceship::right);
      break;
    case sf::Keyboard::Key::W:
      break;
    case sf::Keyboard::Key::S:
      break;
    default:
      // ship.setState(spaceship::stoped);
      break;
    }
    state = PRESS;
  } else if (release) {
    switch (release->code) {
    case sf::Keyboard::Key::W:
    case sf::Keyboard::Key::S:
      ship.setState(spaceship::stoped);
      break;
    case sf::Keyboard::Key::A:
      ship.setState(spaceship::right);
      break;
    case sf::Keyboard::Key::D:
      ship.setState(spaceship::left);
      break;
    default:
      break;
    }
    state = RELEASE;
    // ship.setState(spaceship::stoped);
  } else {
    if (state == RELEASE) {
      ship.setState(spaceship::stoped);
    }
    // ship.setState(spaceship::stoped);
  }
}
