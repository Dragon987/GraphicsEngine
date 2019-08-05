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
        r.Background({0.2f, 0.0f, 0.0f, 0.0f});

        r.BeginDraw(DRAW_MODE_LINES);

        r.Translate(200, 200);
        r.Rotate(a);

        r.Vertex(-100, -100);
        r.Vertex(0, 0);

        r.EndDraw();

        a += 0.01;
        r.SPollEvents();
    }
}