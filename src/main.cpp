#include "../include/background.h"
#include "../include/control.h"
#include "../include/settings.h"
#include "../include/spaceship.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/WindowStyle.hpp>

int main() {
  sf::ContextSettings settings;
  settings.antialiasingLevel = 4;
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "Spacewar!", sf::Style::Default, settings);
  spaceship ship(window);
  control c(ship, window);
  sky &s = sky::instance(window);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    c.update(event);
    ship.update();
    s.update();
    window.display();
  }

  return 0;
}
