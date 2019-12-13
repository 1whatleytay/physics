#pragma once

#include <engine/thing.h>

class Goal : public Thing {
    bool didCelebrate = false;

public:
    void celebrate();

    Goal(const Arguments &arguments);
};