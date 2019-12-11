#include <world/world.h>

#include <engine/texture.h>

void World::key(Key code, Action action) {
    if (action == Action::Pressed && code == Key::P) {
        mainBody->paused = !mainBody->paused;
    }
}

void World::create() {
    mainBody = new Body({ this, { 40, 40, 60, 60 } }, physics, 6, 0.08);

    new Solid({ this, { 20, 200, 400, 10 } }, physics);
    new Solid({ this, { 560, 20, 10, 300 } }, physics);
    new Solid({ this, { 300, 500, 300, 10 }}, physics);
    new Solid({ this, { -400, 700, 4000, 10 } }, physics);
}

int number = 0;

void World::update() {
    float leftWall = mainBody->x;
    float rightWall = mainBody->x + mainBody->width;
    float topWall = mainBody->y;
    float bottomWall = mainBody->y + mainBody->height;

    constexpr float cameraFollowBorder = 40;

    float cameraLeftWall = -offsetX + cameraFollowBorder;
    float cameraRightWall = -offsetX + Engine::windowWidth - cameraFollowBorder;
    float cameraTopWall = -offsetY + cameraFollowBorder;
    float cameraBottomWall = -offsetY + Engine::windowHeight - cameraFollowBorder;

    if (leftWall < cameraLeftWall) {
        offsetX = -(leftWall - cameraFollowBorder);
    }

    if (rightWall > cameraRightWall) {
        offsetX = -(rightWall + cameraFollowBorder);
    }

    if (topWall < cameraTopWall) {
        offsetY = -(topWall - cameraFollowBorder);
    }

    if (bottomWall > cameraBottomWall) {
        offsetY = -(bottomWall + cameraFollowBorder);
    }
}
