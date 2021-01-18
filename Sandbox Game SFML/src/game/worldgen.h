#pragma once
#include "../map/Map.h"

inline TileMap generate_world(Vector2u size) {
    Clock debug;
    TileMap world(Vector2i(size.x, size.y));
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
