#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Atlas : public Texture {
public:
	static Atlas Universal;
	string path;
	Atlas(string path);
	Sprite get_sprite(IntRect);
};
