#include <world/confetti.h>

#include <engine/engine.h>

#include <cmath>

void Confetti::update() {
    if (velocityX > 0 || velocityY > 0 ) {
        x += velocityX;
        y += velocityY;

        velocityX -= 0.08;
        velocityY -= 0.08;
    } else {
        if (framesPast++ % animationSpeed == 0) {
            texture = frames[index++ % frameCount];
        }

        x += ampX * -std::cos(framesPast * static_cast<float>(M_PI) / 240);
        y += fallSpeed;
    }

    save();
}

Confetti::Confetti(const Arguments &arguments) : Thing(arguments) {
    frames = engine->loadTexture("/Users/desgroup/Desktop/confetti.png").split(2, 3);

    index = std::rand() % 5;
    texture = frames[index % frameCount];

    velocityX = static_cast<float>(std::rand() % 100) / 33;
    velocityY = static_cast<float>(std::rand() % 100) / 33;

    ampX = static_cast<float>(std::rand() % 255) / (255 * 3);
    fallSpeed = static_cast<float>(std::rand() % 255) / (255 * 3);

    tintR = static_cast<float>(std::rand() % 255) / 255;
    tintG = static_cast<float>(std::rand() % 255) / 255;
    tintB = static_cast<float>(std::rand() % 255) / 255;

    save();
}