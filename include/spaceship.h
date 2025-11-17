#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class spaceship {
  sf::Vector2f pos;

protected:
  sf::ConvexShape body;
  sf::RenderWindow &window;

public:
  spaceship(sf::RenderWindow &);
  void setPos(sf::Vector2f);
  sf::Vector2f getPos() const;
};

class standart_ship : public spaceship {
public:
  standart_ship(sf::RenderWindow &);
  void update();
};
