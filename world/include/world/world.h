#pragma once

#include <engine/engine.h>

#include <world/body.h>
#include <world/text.h>
#include <world/arrow.h>
#include <world/solid.h>
#include <world/physics.h>

class World : public Engine {
    Physics physics;

    Body *mainBody = nullptr;

protected:
    void key(Key code, Action action) override;

    void create() override;

    void update() override;
};
