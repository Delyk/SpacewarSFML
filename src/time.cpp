#include "../include/time.h"
#include <SFML/Graphics.hpp>

//Глобальный таймер
class clock globalTimer;

/*** Класс таймера ***/
//Конструтор
clock::clock() { update(); }

//Обновление таймера
void clock::update() {
  time = clk.getElapsedTime().asMicroseconds();
  clk.restart();
}

//Получить текущее значение таймера
float clock::getTime() {
  float time = this->time /= 300;
  update();
  return time;
}
