#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "../phys/collision.h"
#include "../gfx/Atlas.h"
#include "../debug/Log.h"
#include "../util.h"

using namespace sf;

class StateMachine {
protected:
	map<String, Uint8> states;
	Uint8 current_state;
	Uint8 prev_state;
	virtual void add_state(string state);
	virtual void do_state_logic(Time delta) {};
	virtual void enter_state(Uint8 new_state) {}
	virtual void exit_state(Uint8 old_state) {}
	virtual Uint8 get_next_state() { return 0; }
};


class Player : public CollisionObject, public StateMachine {
protected:
	Vector2f gravity_force;

public:
	const float GRAVITY_RATIO = 0.8, JUMP_HEIGHT = 4.5 * 16 * GRAVITY_RATIO, JUMP_DURATION = 0.3;
	float speed = 130;
	float gravity = (2 * JUMP_HEIGHT) / powf(JUMP_DURATION, 2);
	float jump = -gravity * JUMP_DURATION;
	float min_jump = jump * 0.85;

	Vector2f move;
	Player();
	Player(Vector2f position);
	void update(Time delta);
	virtual FloatRect get_collision() override;
	virtual void do_state_logic(Time delta) override;
	virtual Uint8 get_next_state() override;
	virtual void exit_state(Uint8 old_state) override;
	virtual void enter_state(Uint8 new_state) override;
};
