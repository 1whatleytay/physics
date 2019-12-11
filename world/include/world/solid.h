#pragma once

#include <engine/thing.h>

class Engine;
class Physics;

class Solid : public Thing {
    Physics &physics;
public:
    void update() override;

    Solid(const Arguments &arguments, Physics &physics);
};