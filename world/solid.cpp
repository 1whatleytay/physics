#include <world/solid.h>

#include <world/physics.h>

#include <engine/engine.h>

void Solid::update() {
}

Solid::Solid(const Arguments &arguments, Physics &physics) : Thing(arguments), physics(physics) {
    physics.collisions.push_back({ x, y, width, height });

    texture = engine->loadTexture("white", [&]() { return Texture(engine, 1, 1, { 255, 0, 255, 255 }); });

    save();
}
