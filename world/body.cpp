#include <world/body.h>

#include <world/text.h>
#include <world/arrow.h>
#include <world/physics.h>

#include <engine/engine.h>

#include <fmt/format.h>

constexpr float arrowStrength = 10;

float Body::calculateFriction() {
    float fn = 9.8f * mass;
    return fn * friction;
}

Force Body::getArrowForce() {
    return { arrow->width * arrowStrength, arrow->height * arrowStrength };
}

void Body::applyForce(Force force) {
    forces.push_back(force);
}
void Body::setMass(float newMass) {
    mass = newMass;
}
void Body::setVelocity(float newVelocityX, float newVelocityY) {
    velocityX = newVelocityX;
    velocityY = newVelocityY;
}

void Body::setFriction(float mew) {
    friction = mew;
}

void Body::doVelocity() {
    for (const Force &force : forces) {
        velocityX += force.x / mass / physics.fps;
        velocityY += force.y / mass / physics.fps;
    }
    forces.clear();

    velocityY += physics.gravity / physics.fps;
}

void Body::doCollision() {
    float thisLeftWall = x;
    float thisRightWall = x + width;
    float thisTopWall = y;
    float thisBottomWall = y + height;

    for (const Collision &col : physics.collisions) {
        float thatLeftWall = col.x;
        float thatRightWall = col.x + col.width;
        float thatTopWall = col.y;
        float thatBottomWall = col.y + col.height;

        if (thisTopWall <= thatBottomWall && thisBottomWall >= thatTopWall) {
            if (thisRightWall <= thatLeftWall && thisRightWall + velocityX > thatLeftWall) {
                discardedVelocityX = velocityX;
                velocityX *= physics.bounceMultiplier;
                x += thatLeftWall - thisRightWall;
            }

            if (thisLeftWall >= thatRightWall && thisLeftWall + velocityX < thatRightWall) {
                discardedVelocityX = velocityX;
                velocityX *= physics.bounceMultiplier;
                x += thatRightWall - thisLeftWall;
            }
        }

        if (thisLeftWall <= thatRightWall && thisRightWall >= thatLeftWall) {
            if (thisTopWall >= thatBottomWall && thisTopWall + velocityY < thatBottomWall) {
                discardedVelocityY = velocityY;
                velocityY *= physics.bounceMultiplier;
                y += thatBottomWall - thisTopWall;
            }

            if (thisBottomWall <= thatTopWall && thisBottomWall + velocityY > thatTopWall) {
                discardedVelocityY = velocityY;
                velocityY *= physics.bounceMultiplier;
                y += thatTopWall - thisBottomWall;
            }
        }
    }
}

void Body::doMovement() {
    if (discardedVelocityX != 0 && velocityY != 0) {
        float velocityYBefore = velocityY;
        float notSignVelocity = velocityY > 0 ? -1 : 1;

        velocityY += notSignVelocity * calculateFriction() / physics.fps;
        if (velocityY > 0 != velocityYBefore > 0)
            velocityY = 0;
    }

    if (discardedVelocityY != 0 && velocityX != 0) {
        float velocityXBefore = velocityX;
        float notSignVelocity = velocityX > 0 ? -1 : 1;

        velocityX += notSignVelocity * calculateFriction() / physics.fps;
        if (velocityX > 0 != velocityXBefore > 0)
            velocityX = 0;
    }

    discardedVelocityX = 0;
    discardedVelocityY = 0;

    x += velocityX;
    y += velocityY;
}

void Body::mouse(float pX, float pY) {
    arrow->pointTo(pX, pY);

    if (selected) {
        Force force = getArrowForce();
        text->x = pX + 10;
        text->y = pY - 30;
        text->modify(fmt::format("{} {}", (int32_t)force.x, (int32_t)force.y));
    }
}

void Body::click(enum Button button, enum Action action) {
    float clickX, clickY;
    engine->getMousePosition(clickX, clickY);

    if (button == Button::Left) {
        if (clickX >= x && clickX <= x + width && clickY >= y && clickY <= y + height) {
            if (action == Action::Pressed && !selected) {
                selected = true;

                arrow->moveTo(clickX, clickY);
                arrow->show(true);
                text->show(true);
            }
        }

        if (action == Action::Released && selected) {
            selected = false;

            applyForce(getArrowForce());
            arrow->show(false);
            text->show(false);
        }
    }
}

void Body::update() {
    if (!paused) {
        doVelocity();
        doCollision();
        doMovement();
    }

    save();
}

Body::Body(const Arguments &arguments, Physics &physics, float mass, float friction)
    : Thing(arguments), physics(physics), mass(mass), friction(friction) {
    arrow = new Arrow(engine, x + width / 2, y + height / 2);
    arrow->show(false);

    text = new Text(engine, x + width / 2, y + height / 2);
    text->fontSize = 2;
    text->show(false);

    texture = engine->loadTexture("red", [&]() { return Texture(engine, 1, 1, { 255, 0, 0, 255 }); });

    save();
}
