#include "./../engine.hpp"

#include <iostream>

#define uint unsigned int

int main()
{
    Renderer r("title", 640, 480);

    double x = 10, y = 10;

        float a = 0.0f;
    while (!r.WindowShouldClose())
    {
        r.Background({0.0f, 0.0f, 0.0f, 0.0f});

        r.FillRect(200, 200, 100, 100, Renderer::RECT_MODE_CENTER, a, {1, 0, 0, 1});

        a += 0.01;
        r.SPollEvents();
    }
}