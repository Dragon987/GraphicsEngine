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

        if (r.GetKey(-1) == GLFW_PRESS)
        {
            std::cout << 'A' << '\n';
        }

        r.SwapBuffers();

        r.PollEvents();
    }
}