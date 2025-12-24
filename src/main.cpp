#include "../include/control.h"
#include "../include/settings.h"
#include "../include/spaceship.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>

int main() {
  sf::ContextSettings settings;
  settings.antiAliasingLevel = 4;
  sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
                          "Spacewar!", sf::State::Windowed, settings);
  window.setFramerateLimit(30);
  spaceship ship(window);
  control &c = control::instance(ship, window);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      } else {
        c.update(event);
      }
    }

    window.clear();
    ship.update();
    window.display();
  }

  return 0;
}
