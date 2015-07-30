#ifndef LINEBREAK_H
#define LINEBREAK_H
#include<SFML/Graphics.hpp>

using namespace sf;
//lineBreak() функция для переноса строки
//параметры: str1-строка над которой будет производится действие
//str2-строка в которую будут перенесены символы, которые не поместились в str1
//numberOfCharacters число символов в str1 после работы функции.
//функция возвращает измененную str1
//ВАЖНО: данные находившиеся в str2 до начала работы функции будут удалены.
String lineBreak(String &str1, String &str2, int numberOfCharacters);
#endif