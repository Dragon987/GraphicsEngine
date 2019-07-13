cmake_minimum_required(VERSION 3.0)
project(GraphicsEngine VERSION 1.0.0)

option(LINUX "Set OS option" ON)

add_library(
    engine SHARED
    ./src/engine.cpp
    ./src/engine.hpp
)
if(LINUX)

    target_link_libraries(
        engine
        -lGL 
        -lGLU 
        -lglfw3 
        -lX11 
        -lXxf86vm 
        -lXrandr 
        -lpthread 
        -lXi 
        -ldl 
        -lXinerama 
        -lXcursor 
        -lGLEW
    )
else()

    target_link_libraries(
        engine
        dep/lib/glew32s
        dep/lib/libglfw3
    )

endif()


add_executable(
    test
    src/test/main.cpp
)

target_link_libraries(
    test
    engine
)

