#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <array>
#include <iostream>
#include <string>
#include <unordered_map>
#include "../debug/Log.h"

using namespace sf;
using namespace std;

class Uint8Matrix {
	Uint8* data = nullptr;
public:
	int width, height;
	Uint8Matrix() : width(0), height(0) {}
	Uint8Matrix(int width, int height);
	~Uint8Matrix();
	Uint8& operator() (int x, int y);
};

struct Tile {
	String name = "";
	Vector2i tex;
	bool solid = true;
};

class TileMap : public sf::Drawable, public sf::Transformable {
	VertexArray m_vertices;
	
	unordered_map<Uint8, Tile> m_tileset{ { 0, Tile{"air", Vector2i(0, 0), false } } };
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Texture tileset_texture;
	const Vector2u tile_size = Vector2u(16, 16);
	Uint8Matrix tiles;

	TileMap(Vector2i size);

	Vector2f convert_coordinate(Vector2f vec);
	Vector2i convert_coordinate(Vector2i vec);

	bool load();

	void set_block(Vector2i location, Uint8);
	void add_tile(Tile t);
	void fill_range(IntRect range, Uint8 id);
	Uint8 get_block(Vector2i location);

	vector<FloatRect> get_collision(FloatRect r);

};
