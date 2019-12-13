#pragma once

#include <engine/thing.h>

class Engine;

class Arrow : public Thing {
    float actualX = 0, actualY = 0;
    float pointingX = 0, pointingY = 0;

    void refresh();

public:
    void moveTo(float pointX, float pointY);
    void pointTo(float pointX, float pointY);

    void getArrowSize(float &lengthX, float &lengthY);

    Arrow(Engine *engine, float x, float y);
};