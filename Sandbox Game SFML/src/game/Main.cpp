#include "../engine.h"
#include "worldgen.h"

int main() {
    
    Clock clock;
    
    Time delta;
    CollisionManager col;
    Player player;
    col.add_object(player);
    TileMap world = generate_world(Vector2u(256, 144));
    col.set_map(world);

    UI::Panel panel(FloatRect(50, 50, 50, 50));
    UI::Button button(FloatRect(10, 10, 10, 10));
    panel.setFillColor(Color::White);
    button.setFillColor(Color::Blue);
    panel.add_child(button);

    RenderWindow window(sf::VideoMode(1280, 720), "My window");
    View camera(FloatRect(0, 0, 640, 360));
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    while (window.isOpen()) {
        delta = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {

            case Event::Closed :
                window.close();
                break;
            case Event::KeyPressed:
                if (event.key.code == Keyboard::P)
                    cout << 1 / delta.asSeconds() << endl;
            }

        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
            panel.setPosition(mouse);
            mouse.x /= world.tile_size.x;
            mouse.y /= world.tile_size.y; 
            world.set_block(Vector2i(mouse.x, mouse.y), 0);
        }

        player.update(delta);
        col.tick(delta);
        camera.setCenter(player.getPosition());

        window.setView(camera);
        window.clear(sf::Color::Black);
        window.draw(world);
        window.draw(player);
        panel.draw(window);
        window.display();
        
    }
    return 0;
}