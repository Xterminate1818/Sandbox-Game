#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include "../map/Map.h"
#include "../debug/Log.h"
#include "../util.h"

using namespace sf;
using namespace std;

// Namespace rather than enum bc weird enum rules wont allow it
namespace Normal {
	const Vector2f NONE = Vector2f(0, 0);
	const Vector2f UP = Vector2f(0, -1);
	const Vector2f DOWN = Vector2f(0, 1);
	const Vector2f LEFT = Vector2f(-1, 0);
	const Vector2f RIGHT = Vector2f(1, 0);
}

struct CollisionEvent {
	Vector2f normal = Normal::NONE;
	float time = 1.f;
};

class CollisionObject : public Sprite {
public:
	static Vector2f floor_dir;
	Vector2f velocity;
	vector<Vector2f> touching;
	virtual bool is_touching(Vector2f normal);
	virtual bool is_on_floor();
	virtual FloatRect get_collision() { return getGlobalBounds(); };
	virtual void on_collision(CollisionEvent, Vector2f velocity) {}
};

CollisionEvent sweep_rect(const FloatRect& r1, Vector2f velocity, const FloatRect& r2);

FloatRect get_broad_range(const FloatRect& rect, Vector2f velocity);

class CollisionManager {
protected:
	TileMap* map = nullptr;
	vector<CollisionObject*> objects;

public:
	void tick(Time delta);
	void set_map(TileMap& tm);
	void add_object(CollisionObject& obj);
};

