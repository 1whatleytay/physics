add_library(world
    include/world/body.h
    include/world/solid.h
    include/world/world.h
    include/world/physics.h
    include/world/arrow.h
    include/world/text.h
    include/world/goal.h
    include/world/confetti.h

    body.cpp
    solid.cpp
    world.cpp
    physics.cpp
    arrow.cpp
    text.cpp
    goal.cpp
    confetti.cpp)

target_include_directories(world PUBLIC include)
target_link_libraries(world PUBLIC fmt engine)