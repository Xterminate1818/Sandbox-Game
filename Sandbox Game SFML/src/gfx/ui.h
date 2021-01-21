#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

/* 
* Implementation:
* Create a container element with all other elements as children.
* Pass it a MouseState object every frame, with the mouse position
* adjusted for the window's scaling.
*/


namespace UI {

	struct MouseState {
		Vector2u position;
		bool click, handled = false;
	};

	struct Element : public RectangleShape {
		Vector2f local_pos;
		inline Element(FloatRect r) {
			local_pos = Vector2f(r.left, r.top);
			setSize(Vector2f(r.width, r.height));
		}

		virtual void handle_mouse_input(MouseState&) {}

		inline void update(MouseState& m) {
			handle_mouse_input(m);
			if (m.handled) return;
			for (auto& c : children) c.update(m);
		}

		inline void draw(sf::RenderTarget& target) {
			RectangleShape* rect = this; // Polymorphic bullshit
			FloatRect fr = rect->getGlobalBounds();
			target.draw(*rect, RenderStates());
			for (auto& child : children) {
				println(Vector2f(fr.left, fr.top));
				child.setPosition(Vector2f(fr.left, fr.top) + child.local_pos);
				child.draw(target);
			}
		}

		inline void add_child(Element child) {
			children.push_back(child);
		}
	protected:
		vector<Element> children;

	};

	class Button : public Element {
	public:
		bool is_hovering = false;
		bool is_clicked = false;

		inline Button(FloatRect r) : Element(r) {}

		void on_mouse_click() {}
		void on_mouse_release() {}
		void on_mouse_entered() {}
		void on_mouse_left() {}

		inline virtual void handle_mouse_input(MouseState& m) override {
			FloatRect bounds = getGlobalBounds();

			if (bounds.contains(m.position.x, m.position.y)) {
				if (!is_hovering) {
					is_hovering = true;
					on_mouse_entered();
				}
				if (m.click && !is_clicked) {
					is_clicked = true;
					on_mouse_click();
					m.handled = true;
				}
				if (!m.click && is_clicked) {
					is_clicked = false;
					on_mouse_release();
				}
			}

			else {
				if (is_hovering) {
					is_hovering = false;
					on_mouse_left();
				}
				if (is_clicked) {
					is_clicked = false;
				}
			}

		}
	};

	class Panel : public Element {
	public:
		Panel(FloatRect r) : Element(r) {}
	};
}