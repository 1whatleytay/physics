#include <engine/thing.h>

#include <engine/engine.h>
#include <engine/texture.h>

Arguments::Arguments(Engine *engine, Position position) : engine(engine), position(position) { }
Arguments::Arguments(Engine *engine) : Arguments(engine, { }) { }

// Temporary solution to make sure engine is able to keep track of positioning after something is hidden.
bool Thing::isMatchingIndex(uint32_t value) {
    return value == index || value == index + Engine::maxThings;
}

std::vector<float> Thing::createData() {
    float x1 = 0, y1 = 0;
    float x2 = 0, y2 = 0;

    texture.getData(x1, y1, x2, y2);

    return {
        x, y, x1, y1,
        x, y + height, x1, y2,
        x + width, y + height, x2, y2,

        x, y, x1, y1,
        x + width, y + height, x2, y2,
        x + width, y, x2, y1,
    };
}

void Thing::save() {
    std::vector<float> data = createData();
    glBufferSubData(GL_ARRAY_BUFFER, index * Thing::objectSize, Thing::objectSize, data.data());
}

void Thing::setPosition(const Position &position) {
    x = position.x;
    y = position.y;

    width = position.width;
    height = position.height;
}

void Thing::key(Key key, Action action) { }
void Thing::mouse(float x, float y) { }
void Thing::click(Button button, Action action) { }
void Thing::update() { }

void Thing::show(bool value) {
    for (size_t a = 0; a < engine->drawOrder.size(); a++) {
        if (value) {
            if (engine->drawOrder[a] == index + Engine::maxThings) {
                engine->drawOrder[a] = index;
                break;
            }
        } else {
            if (engine->drawOrder[a] == index) {
                engine->drawOrder[a] = index + Engine::maxThings;
                break;
            }
        }
    }
}

void Thing::remove() {
    engine->removeThing(this);
}

Thing::Thing(const Arguments &arguments) : engine(arguments.engine), index(arguments.engine->registerThing(this)) {
    setPosition(arguments.position);
}
