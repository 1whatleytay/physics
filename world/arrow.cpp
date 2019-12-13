#include <world/arrow.h>

#include <engine/engine.h>

#include <cmath>

void Arrow::refresh() {
    float xLength = pointingX - actualX;
    float yLength = pointingY - actualY;

    float length = std::sqrt(xLength * xLength + yLength * yLength);

    x = actualX;
    y = actualY - length / 2;

    width = length;
    height = length;

    originX = actualX;
    originY = actualY;
    rotation = std::asin(yLength / length);
    if (xLength < 0) {
        rotation *= -1;
        rotation += static_cast<float>(M_PI);
    }


    save();
}

void Arrow::moveTo(float pointX, float pointY) {
    actualX = pointX;
    actualY = pointY;

    refresh();
}

void Arrow::pointTo(float pointX, float pointY) {
    pointingX = pointX;
    pointingY = pointY;

    refresh();
}

void Arrow::getArrowSize(float & lengthX, float & lengthY) {
    lengthX = pointingX - actualX;
    lengthY = pointingY - actualY;
}

Arrow::Arrow(Engine *engine, float x, float y) : Thing({ engine, { x, y, 0, 0 } }) {
    texture = engine->loadTexture("/Users/desgroup/Desktop/arrow.png");

    save();
}