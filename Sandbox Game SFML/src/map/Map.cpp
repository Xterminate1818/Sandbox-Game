#include "Map.h"

Uint8Matrix::Uint8Matrix(int w, int h) {
	width = w;
	height = h;
	data = new Uint8[width * height];
    for (int i = 0; i < width * height; i++) {
        data[i] = 0;
    }
}

Uint8Matrix::~Uint8Matrix() {
	//delete data;
}

Uint8& Uint8Matrix::operator() (int x, int y) {
	if (x < 0 || x >= width || y < 0 || y >= height) {
		cout << "Index (" << x << ", " << y << ") is out of bounds!" << endl;
		throw 1;
	}
	return data[(x * height) + y];
}


TileMap::TileMap(Vector2i size) {
    tiles = Uint8Matrix(size.x, size.y);
    m_vertices.resize(tiles.width * tiles.height * 4);
}

Vector2f TileMap::convert_coordinate(Vector2f vec) {
    return Vector2f(vec.x / tile_size.x, vec.y / tile_size.y);
}

Vector2i TileMap::convert_coordinate(Vector2i vec) {
    return Vector2i(vec.x / tile_size.x, vec.y / tile_size.y);
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &tileset_texture;

    // draw the vertex array
    target.draw(m_vertices, states);
}

bool TileMap::load() {
            
    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(tiles.width * tiles.height * 4);

    // populate the vertex array, with one quad per tile
    for (int x = 0; x < tiles.width; ++x)
        for (int y = 0; y < tiles.height; ++y)
        {
            // get the current tile number
            Uint8 tileID = tiles(x, y);

            // find its position in the tileset texture
            Vector2i tex = m_tileset[tileID].tex;

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(x + y * tiles.width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(x * tile_size.x, y * tile_size.y);
            quad[1].position = sf::Vector2f((x + 1) * tile_size.x, y * tile_size.y);
            quad[2].position = sf::Vector2f((x + 1) * tile_size.x, (y + 1) * tile_size.y);
            quad[3].position = sf::Vector2f(x * tile_size.x, (y + 1) * tile_size.y);

            // Already done when blocks are placed

            // define its 4 texture coordinates
            /*
            quad[0].texCoords = sf::Vector2f(tex.x, tex.y);
            quad[1].texCoords = sf::Vector2f(tex.x + tile_size.x, tex.y);
            quad[2].texCoords = sf::Vector2f(tex.x + tile_size.x, tex.y + tile_size.y);
            quad[3].texCoords = sf::Vector2f(tex.x, tex.y + tile_size.y);
            */
        }

    return true;
}

void TileMap::set_block(Vector2i loc, Uint8 id) {
	if (loc.x < 0 || loc.y < 0 || loc.x >= tiles.width || loc.y >= tiles.height) {
		cout << "set_block(" << loc.x << ", " << loc.y << ") is out of bounds" << endl;
		return;
	}
	tiles(loc.x, loc.y) = id;

    // Updating mesh
    Vector2i tex = m_tileset[id].tex;
    sf::Vertex* quad = &m_vertices[(loc.x + loc.y * tiles.width) * 4];

    quad[0].texCoords = sf::Vector2f(tex.x, tex.y);
    quad[1].texCoords = sf::Vector2f(tex.x + tile_size.x, tex.y);
    quad[2].texCoords = sf::Vector2f(tex.x + tile_size.x, tex.y + tile_size.y);
    quad[3].texCoords = sf::Vector2f(tex.x, tex.y + tile_size.y);
}

void TileMap::fill_range(IntRect range, Uint8 id) {
	for (int x = 0; x < range.width; x++)
		for (int y = 0; y < range.height; y++)
			set_block(Vector2i(x + range.left, y + range.top), id);
}

void TileMap::add_tile(Tile t) {
    m_tileset[m_tileset.size()] = t;
}

Uint8 TileMap::get_block(Vector2i location) {
    return tiles(location.x, location.y);
}

vector<FloatRect> TileMap::get_collision(FloatRect rect) {
    int startx = fmax(floor(rect.left / tile_size.x), 0.f);
    int starty = fmax(floor(rect.top / tile_size.y), 0.f);
    int endx = fmin(startx + (ceil(rect.width / tile_size.x) + 1), tiles.width);
    int endy = fmin(starty + (ceil(rect.height / tile_size.y) + 1), tiles.height);
    vector<FloatRect> r;

    for (int x = startx; x < endx; x++) {
        for (int y = starty; y < endy; y++) {
            if (tiles(x, y) > 0 && m_tileset[tiles(x, y)].solid) {
                r.push_back(FloatRect{ 
                    (float)x * tile_size.x, 
                    (float)y * tile_size.y, 
                    (float)tile_size.x, 
                    (float)tile_size.y 
                    });
            }
        }
    }
    return r;
}