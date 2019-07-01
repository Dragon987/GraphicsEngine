cmake_minimum_required(VERSION 3.0)
project(GraphicsEngine VERSION 1.0.0)

add_library(
    libengine
    engine.cpp
    engine.hpp
)

target_link_libraries(
    libengine
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

add_executable(
    test
    main.cpp
)

target_link_libraries(
    test
    libengine
)

