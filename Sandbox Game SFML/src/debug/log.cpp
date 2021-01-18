#include "Log.h"

void print(std::string i) {
	std::cout << i;
}
void print(int i) {
	std::cout << i;
}
void print(float i) {
	std::cout << i;
}
void print(sf::Vector2f i) {
	std::cout << i.x << ", " << i.y;
}
void print(sf::Vector2i i) {
	std::cout << i.x << ", " << i.y;
}
void print(sf::Vector2u i) {
	std::cout << i.x << ", " << i.y;
}
void print(sf::Time i) {
	if (i.asSeconds() >= 1)
		std::cout << i.asSeconds() << " seconds";
	else if (i.asMilliseconds() >= 1) 
		std::cout << i.asMilliseconds() << " milliseconds";
	else 
		std::cout << i.asMicroseconds() << " microseconds";

}
void print(sf::FloatRect i) {
	std::cout 
		<< "x = " << i.left
		<< "; y = " << i.top
		<< "; w = " << i.width
		<< "; h = " << i.height
		<< ";";
}

void println(std::string i) {
	print(i);
	std::cout << std::endl;
}
void println(int i) {
	print(i);
	std::cout << std::endl;
}
void println(float i) {
	print(i);
	std::cout << std::endl;
}
void println(sf::Vector2f i) {
	print(i);
	std::cout << std::endl;
}
void println(sf::Vector2i i) {
	print(i);
	std::cout << std::endl;
}
void println(sf::Vector2u i) {
	print(i);
	std::cout << std::endl;
}
void println(sf::Time i) {
	print(i);
	std::cout << std::endl;
}
void println(sf::FloatRect i) {
	print(i);
	std::cout << std::endl;
}
