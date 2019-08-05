#include "./../engine.hpp"

#include <iostream>

#define uint unsigned int

int main()
{
    Renderer r("title", 500, 500);

    double x = 10, y = 10;

<<<<<<< HEAD
    float a = 0.0f;
=======
        float a = 0.0f;
>>>>>>> 2ded8531049a471ad222244ad45e6ad8c6b5db6e
    while (!r.WindowShouldClose())
    {
        r.Background({0.2f, 0.0f, 0.0f, 0.0f});

<<<<<<< HEAD
        r.BeginDraw(DRAW_MODE_LINES);

        r.Translate(200, 200);
        r.Rotate(a);

        r.Vertex(-100, -100);
        r.Vertex(0, 0);

        r.EndDraw();
=======
        r.FillRect(200, 200, 100, 100, Renderer::RECT_MODE_CENTER, a, {1, 0, 0, 1});
>>>>>>> 2ded8531049a471ad222244ad45e6ad8c6b5db6e

        a += 0.01;
        r.SPollEvents();
    }
}