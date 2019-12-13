#pragma once

#include <engine/thing.h>

class Confetti : public Thing {
    constexpr static uint32_t frameCount = 5;
    constexpr static uint32_t animationSpeed = 60;

    std::vector<Texture> frames;
    uint32_t index = 0;
    uint32_t framesPast = 0;

    float velocityX = 0;
    float velocityY = 0;

    float ampX = 0;
    float fallSpeed = 0;
public:
    void update() override;

    explicit Confetti(const Arguments &arguments);
};