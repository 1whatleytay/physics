#include <world/world.h>

#include <engine/texture.h>

#include <fmt/format.h>

void World::key(Key code, Action action) {
    if (action == Action::Pressed && code == Key::P) {
        mainBody->paused = !mainBody->paused;
    }
}

void World::create() {
    mainBody = new Body({ this, { 40, 40, 20, 20 } }, physics, 6, 0.08);

    new Solid({ this, { 20, 200, 400, 10 } }, physics);
    new Solid({ this, { 560, 20, 10, 300 } }, physics);
    new Solid({ this, { 300, 500, 300, 10 }}, physics);
    new Solid({ this, { -400, 700, 4000, 10 } }, physics);

    goal = new Goal({ this, { 800, 550, 96, 150 } });

    tooltip = new Text(this, 40, 40);
}

void World::update() {
//    float leftWall = mainBody->x;
//    float rightWall = mainBody->x + mainBody->width;
//    float topWall = mainBody->y;
//    float bottomWall = mainBody->y + mainBody->height;
//
//    constexpr float cameraFollowBorder = 40;
//
//    float cameraLeftWall = -offsetX + cameraFollowBorder;
//    float cameraRightWall = -offsetX + Engine::windowWidth - cameraFollowBorder;
//    float cameraTopWall = -offsetY + cameraFollowBorder;
//    float cameraBottomWall = -offsetY + Engine::windowHeight - cameraFollowBorder;
//
//    if (leftWall < cameraLeftWall) {
//        offsetX = -(leftWall - cameraFollowBorder);
//    }
//
//    if (rightWall > cameraRightWall) {
//        offsetX = -(rightWall + cameraFollowBorder);
//    }
//
//    if (topWall < cameraTopWall) {
//        offsetY = -(topWall - cameraFollowBorder);
//    }
//
//    if (bottomWall > cameraBottomWall) {
//        offsetY = -(bottomWall + cameraFollowBorder);
//    }

    float clickX = mainBody->x + mainBody->width / 2;
    float clickY = mainBody->y + mainBody->height / 2;

    if (clickX >= goal->x && clickX <= goal->x + goal->width && clickY >= goal->y && clickY <= goal->y + goal->height) {
        goal->celebrate();
    }

    offsetX = -(mainBody->x + mainBody->width / 2 - static_cast<float>(Engine::windowWidth) / 2);
    offsetY = -(mainBody->y + mainBody->height / 2 - static_cast<float>(Engine::windowHeight) / 2);

    tooltip->x = 40 - offsetX;
    tooltip->y = 40 - offsetY;
    tooltip->modify(fmt::format("{} Shots Taken", mainBody->shotsTaken));


}
