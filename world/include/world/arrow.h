#pragma once

#include <engine/thing.h>

class Engine;

class Arrow : public Thing {
public:
    void moveTo(float pointX, float pointY);
    void pointTo(float pointX, float pointY);

    void update() override;

    Arrow(Engine *engine, float x, float y);
};