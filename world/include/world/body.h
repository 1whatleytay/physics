#pragma once

#include <engine/thing.h>

class Text;
class Arrow;
class Engine;
class Physics;

class Force {
public:
    float x; // N horizontal
    float y; // N vertical
};

class Body : public Thing {
    Physics &physics;

    float mass = 0; // kg
    std::vector<Force> forces;

    bool selected = false;
    Arrow *arrow = nullptr;
    Text *text = nullptr;

    float velocityX = 0;
    float velocityY = 0;

    float discardedVelocityX = 0;
    float discardedVelocityY = 0;

    float friction = 0;

    float calculateFriction();
    Force getArrowForce();

    void doVelocity();
    void doCollision();
    void doMovement();
public:
    bool paused = false;

    void applyForce(Force force);
    void setMass(float newMass);
    void setVelocity(float newVelocityX, float newVelocityY);
    void setFriction(float mew);

    void mouse(float pX, float pY) override;
    void click(Button button, Action action) override;

    void update() override;

    Body(const Arguments &arguments, Physics &physics, float mass, float friction);
};
