#include <world/goal.h>

#include <world/confetti.h>

#include <engine/engine.h>

void Goal::celebrate() {
    if (!didCelebrate) {
        for (uint32_t a = 0; a < 20; a++) {
            new Confetti({engine, { x + width / 2, y, 10, 10 }});
        }
        
        didCelebrate = true;
    }
}

Goal::Goal(const Arguments &arguments) : Thing(arguments) {
    texture = engine->loadTexture("/Users/desgroup/Desktop/pole.png");

    tintB = 0;

    save();
}