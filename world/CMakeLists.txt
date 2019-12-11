add_library(world
    include/world/body.h
    include/world/solid.h
    include/world/world.h

    body.cpp
    solid.cpp
    world.cpp include/world/physics.h physics.cpp include/world/arrow.h arrow.cpp include/world/text.h text.cpp)

target_include_directories(world PUBLIC include)
target_link_libraries(world PUBLIC fmt engine)