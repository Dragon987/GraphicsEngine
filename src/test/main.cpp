#include "./../engine.hpp"

#include <iostream>

#define uint unsigned int

int main()
{
    Renderer r("title", 640, 480);

    double x = 10, y = 10;

    while (!r.WindowShouldClose())
    {
        r.Background({0.0f, 0.0f, 0.0f, 0.0f});

        r.BeginDraw(DRAW_MODE_LINES);
        r.Fill({1, 0, 0, 0});
        r.Vertex(0, 0);
        r.Vertex(640, 480);

        r.EndDraw();


        r.GetMousePos(&x, &y);

        std::cout << "X: " << x << ", Y: " << y << ".\n";

        r.BeginDraw(DRAW_MODE_LINES);
        r.Fill({0, 0, 1, 0});

        r.Vertex(x, y);
        r.Vertex(100, 200);

        r.EndDraw();

        r.BeginDraw(DRAW_MODE_LINES);
        r.Vertex(100, 200);
        r.Vertex(200, 200);

        r.EndDraw();

        r.SwapBuffers();

        r.PollEvents();
    }
}