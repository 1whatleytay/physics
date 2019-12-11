#include <world/arrow.h>

#include <engine/engine.h>

void Arrow::moveTo(float pointX, float pointY) {
    float pointingX = width + x;
    float pointingY = height + y;

    x = pointX;
    y = pointY;

    pointTo(pointingX, pointingY);
}

void Arrow::pointTo(float pointX, float pointY) {
    width = pointX - x;
    height = pointY - y;

    save();
}

void Arrow::update() { }

Arrow::Arrow(Engine *engine, float x, float y) : Thing({ engine, { x, y, 0, 0 } }) {
    texture = engine->loadTexture("/Users/desgroup/Desktop/arrow.png");

    save();
}