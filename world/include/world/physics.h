#include <vector>

class Collision {
public:
    float x = 0, y = 0;
    float width = 0, height = 0;
};

class Physics {
public:
    std::vector<Collision> collisions;

    float gravity = 3;
    float bounceMultiplier = -0.4;
    float fps = 120;
};