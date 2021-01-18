#include <SFML/Graphics.hpp>
#include <memory>
#include "gfx/Atlas.h"
#include "map/Map.h"
#include "debug/Log.h"
#include "entity/Entity.h"
#include "phys/collision.h"


TileMap load_world() {
    Clock debug;
    TileMap world(Vector2i(256, 144));
    world.tileset_texture.loadFromFile("highres atlas.png");
    world.add_tile(Tile{ "grass", Vector2i(32, 0) }); // 1
    world.add_tile(Tile{ "dirt", Vector2i(16, 0) }); // 2
    world.add_tile(Tile{ "stone", Vector2i(0, 16) }); // 3

    debug.restart();
    print("Placing grass...    ");
    world.fill_range(IntRect(0, 4, world.tiles.width, 1), 1);
    print("Done in "); println(debug.restart());

    print("Placing dirt...    ");
    world.fill_range(IntRect(0, 5, world.tiles.width, world.tiles.height - 5), 2);
    print("Done in "); println(debug.restart());

    print("Placing stone...    ");
    world.fill_range(IntRect(0, 15, world.tiles.width, world.tiles.height - 15), 3);
    print("Done in "); println(debug.restart());

    print("Loading world...    ");
    world.load();
    print("Done in "); println(debug.restart());
    return world;
}

int main() {
    CollisionManager col;
    Clock clock;
    TileMap world = load_world();
    Time delta;
    Player player;
    col.add_object(player);
    col.set_map(world);

    RenderWindow window(sf::VideoMode(1280, 720), "My window");
    View camera(FloatRect(0, 0, 640, 360));
    //window.setFramerateLimit(30);
    
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
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            // left mouse button is pressed: shoot
            Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
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
        window.display();
        
    }
    return 0;
}