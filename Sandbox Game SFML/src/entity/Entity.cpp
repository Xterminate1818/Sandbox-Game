#include "Entity.h"

void StateMachine::add_state(string state) {
	states[state] = states.size();
}

Player::Player() {
	setTexture(Atlas::Universal);
	setTextureRect(
		IntRect{ 96, 0, 20, 32 }
	);
	setOrigin(10, 16);

	add_state("idle");
	add_state("run");
	add_state("fall");
	add_state("jump");
}

Player::Player(Vector2f pos) {
	setTexture(Atlas::Universal);
	setTextureRect(
		IntRect{ 24, 0, 8, 16 }
	);
	setPosition(pos);
}

void Player::update(Time delta) {
	Vector2f movedir = Vector2f();
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		movedir.y -= 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		movedir.y += 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		movedir.x -= 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		movedir.x += 1;
	}
	movedir.x *= speed;
	move = movedir;
	do_state_logic(delta);
}

FloatRect Player::get_collision() {
	FloatRect rect = getGlobalBounds();
	rect.left += 7;
	rect.width -= 9;
	return rect;
}

void Player::do_state_logic(Time delta) {
	current_state = get_next_state();
	if (current_state != prev_state) {
		exit_state(prev_state);
		enter_state(current_state);
	}
	prev_state = current_state;
	if (current_state == states["idle"]) {
		velocity.x = lerp(velocity.x, 0, 0.6 * delta.asSeconds() * 25);
		velocity.y = 1;
	}
	else if (current_state == states["run"]) {
		velocity.x = lerp(velocity.x, move.x, 0.6 * delta.asSeconds() * 25);
		velocity.y = 1;
	}
	else if (current_state == states["fall"]) {
		velocity.x = lerp(velocity.x, move.x, 0.2 * delta.asSeconds() * 20);
		velocity.y = fmin(velocity.y + gravity * delta.asSeconds(), 350);
		velocity.y = lerp(velocity.y, 350, 0.2 * delta.asSeconds() * 15);
	}
	else if (current_state == states["jump"]) {
		velocity.x = lerp(velocity.x, move.x, 0.2 * delta.asSeconds() * 20);
		velocity.y = fmin(velocity.y + (gravity * GRAVITY_RATIO) * delta.asSeconds(), 0);
	}
}

Uint8 Player::get_next_state() {
	if (current_state == states["idle"]) {
		if (!is_on_floor()) return states["fall"];
		if (move.y < 0) return states["jump"];
		if (move.x != 0) return states["run"];
	}
	else if (current_state == states["run"]) {
		if (!is_on_floor()) return states["fall"];
		if (move.y < 0) return states["jump"];
		if (move.x == 0) return states["idle"];
	}
	else if (current_state == states["fall"]) {
		bool grounded = is_on_floor();
		if (grounded && move.x == 0) return states["idle"];
		if (grounded && move.x != 0) return states["run"];
	}
	else if (current_state == states["jump"]) {
		if (is_on_floor()) return states["idle"];
		if (move.y >= 0 && velocity.y > min_jump) return states["fall"];
		if (velocity.y >= 0) return states["fall"];
	}
	return current_state;
}

void Player::exit_state(Uint8 old_state) {

}

void Player::enter_state(Uint8 new_state) {
	if (new_state == states["jump"]) {
		velocity.y = jump;
	}
}
