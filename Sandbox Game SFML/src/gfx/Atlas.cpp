#include "Atlas.h"

Atlas::Atlas(string path) {
	this->path = path;
	loadFromFile(path);
	setSmooth(false);
}

Sprite Atlas::get_sprite(IntRect r) {
	Sprite s;
	s.setTexture(*this);
	s.setTextureRect(r);
	return s;
}

Atlas Atlas::Universal = Atlas("highres atlas.png"); // Bruh moment

