#ifndef HP_BAR
#define HP_BAR
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
using namespace sf;
/* Функция рендера полоски жизей.
 * hp - количество здоровья (0..100), position - верхний левый угол полоски,
 * size - размер и пропорции полоски, window - окно, что будет ренерить,
 * color - цвет полоски
 * Закгруглённые края/ косые края / красоту сделаю по просьбе художника, вариантов много, жду предложения
 */
void renderHpBar(int hp, Vector2f position, Vector2f size, RenderWindow &window, Color color = Color::Red);
void renderHpBar(int hp, float pos_x,float pos_y, float size_x,float size_y,
								RenderWindow &window, Color color = Color::Red);
#endif // HP_BAR

