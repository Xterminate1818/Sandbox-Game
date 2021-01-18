#pragma once
#include <iostream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

void print(std::string);
void print(int);
void print(float);
void print(sf::Vector2i);
void print(sf::Vector2f);
void print(sf::Vector2u);
void print(sf::Time);
void print(sf::FloatRect);

void println(std::string);
void println(int);
void println(float);
void println(sf::Vector2i);
void println(sf::Vector2f);
void println(sf::Vector2u);
void println(sf::Time);
void println(sf::FloatRect);
