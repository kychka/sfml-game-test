#ifndef LINEBREAK_H
#define LINEBREAK_H
#include<SFML/Graphics.hpp>

using namespace sf;
//lineBreak() функция для переноса строки
//параметры: str1-строка над которой будет производится действие
//numberOfCharacters число символов в str1 после работы функции.
//функция возвращает измененную str1
String lineBreak(String &str1, int numberOfCharacters);
#endif