#include "./../engine.hpp"

#include <iostream>

#define uint unsigned int

int main()
{
    Renderer r("title", 500, 500);

    double x = 10, y = 10;

    float a = 0.0f;
    while (!r.WindowShouldClose())
    {
        r.Background({0.0f, 0.0f, 0.0f, 0.0f});

        r.FillEllipse(350, 250, 100, 120, a, {1, 1, 1, 1});
        r.DrawCircle(250, 250, 100, {0, 1, 0, 1});

        

        a += 0.01;
        r.SPollEvents();
    }
}