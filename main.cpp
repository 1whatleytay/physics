#include "world/include/world/world.h"

int main() {
    glfwInit();
    World().start();
    glfwTerminate();

    return 0;
}
