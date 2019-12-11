#pragma once

#include <engine/events.h>
#include <engine/texture.h>

#include <vector>

class Engine;

class Position {
public:
    float x = 0, y = 0;
    float width = 0, height = 0;
};

class Arguments {
public:
    Engine *engine;

    Position position = { };

    explicit Arguments(Engine *engine);
    Arguments(Engine *engine, Position position);
};

class Thing {
    static constexpr uint32_t vertexSize = 4 * sizeof(float);
    static constexpr uint32_t objectSize = 6 * vertexSize;

    uint32_t index;

    bool isMatchingIndex(uint32_t value);
    std::vector<float> createData();

    friend class Engine;

protected:
    Engine *engine;

    void save();

    virtual void key(Key key, Action action);
    virtual void mouse(float x, float y);
    virtual void click(Button button, Action action);

    virtual void update();

public:
    float x = 0;
    float y = 0;

    float width = 0;
    float height = 0;

    Texture texture;

    void show(bool value);
    void remove();
    void setPosition(const Position &position);

    explicit Thing(const Arguments &arguments);
    virtual ~Thing() = default;
};
