#include "collision.h"

CollisionEvent sweep_rect(const FloatRect& moving, Vector2f velocity, const FloatRect& still) {
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	if (velocity.x > 0.0f) {
		xInvEntry = still.left - (moving.left + moving.width);
		xInvExit = (still.left + still.width) - moving.left;
	}
	else {
		xInvEntry = (still.left + still.width) - moving.left;
		xInvExit = still.left - (moving.left + moving.width);
	}

	if (velocity.y > 0.0f) {
		yInvEntry = still.top - (moving.top + moving.height);
		yInvExit = (still.top + still.height) - moving.top;
	}
	else {
		yInvEntry = (still.top + still.height) - moving.top;
		yInvExit = still.top - (moving.top + moving.height);
	}


	float xEntry, yEntry;
	float xExit, yExit;

	if (velocity.x == 0.0f) {
		xEntry = -INFINITY;
		xExit = INFINITY;
	}
	else {
		xEntry = xInvEntry / velocity.x;
		xExit = xInvExit / velocity.x;
	}

	if (velocity.y == 0.0f) {
		yEntry = -INFINITY;
		yExit = INFINITY;
	}
	else {
		yEntry = yInvEntry / velocity.y;
		yExit = yInvExit / velocity.y;
	}

	float entryTime = fmax(xEntry, yEntry);
	float exitTime = fmin(xExit, yExit);
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f) {
		return CollisionEvent{};
	}
	else {	// if there was a collision 
		CollisionEvent c;
		// calculate normal of collided surface
		if (xEntry > yEntry) {
			if (xInvEntry < 0.0f)
				c.normal = Normal::RIGHT;
			else
				c.normal = Normal::LEFT;
		}
		else {
			if (yInvEntry < 0.0f)
				c.normal = Normal::DOWN;
			else
				c.normal = Normal::UP;
		}
		c.time = entryTime;
		return c;
	}
}

FloatRect get_broad_range(const FloatRect& rect, Vector2f velocity) {
	FloatRect broadphasebox;
	broadphasebox.left = velocity.x > 0 ? rect.left : rect.left + velocity.x;
	broadphasebox.top = velocity.y > 0 ? rect.top : rect.top + velocity.y;
	broadphasebox.width = velocity.x > 0 ? velocity.x + rect.width : rect.width - velocity.x;
	broadphasebox.height = velocity.y > 0 ? velocity.y + rect.height : rect.height - velocity.y;

	return broadphasebox;
}

void CollisionManager::tick(Time delta) {
	for (auto obj : objects) {
		obj->touching.clear();
		FloatRect rect = obj->get_collision();
		Vector2f velocity = obj->velocity;
		velocity.x *= delta.asSeconds();
		velocity.y *= delta.asSeconds();
		bool finished = false;
		while (!finished) {
			FloatRect broadrange = get_broad_range(rect, velocity);
			CollisionEvent nearest;

			for (auto test : objects) {
				if (test == obj) continue;
				FloatRect testrect = test->get_collision();
				if (!broadrange.intersects(testrect)) continue;
				CollisionEvent col = sweep_rect(rect, velocity, testrect);
				if (col.time <= nearest.time) nearest = col;
			}

			for (FloatRect r : map->get_collision(broadrange)) {
				if (!broadrange.intersects(r)) continue;
				CollisionEvent col = sweep_rect(rect, velocity, r);
				if (col.time <= nearest.time) nearest = col;
			}
			obj->move(velocity.x * nearest.time, velocity.y * nearest.time);

			if (nearest.time == 1) {
				finished = true;
			}
			else {
				obj->touching.push_back(nearest.normal);
				obj->velocity.x *= -nearest.normal.y * (1 - nearest.time);
				obj->velocity.y *= -nearest.normal.x * (1 - nearest.time);
				velocity.x *= -nearest.normal.y * (1 - nearest.time);
				velocity.y *= -nearest.normal.x * (1 - nearest.time);
			}
		}
	}
}

void CollisionManager::set_map(TileMap& tm) {
	map = &tm;
}

void CollisionManager::add_object(CollisionObject& obj) {
	objects.push_back(&obj);
}

Vector2f CollisionObject::floor_dir = Normal::UP;

bool CollisionObject::is_touching(Vector2f normal) {
	for (auto& v : touching) {
		if (v == normal) return true;
	}
	return false;
}

bool CollisionObject::is_on_floor() {
	return is_touching(Normal::UP);
}

