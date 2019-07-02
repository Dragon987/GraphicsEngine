#include "./../engine.hpp"

#define uint unsigned int

int main()
{
    Renderer r("title", 640, 480);

    while (!r.WindowShouldClose())
    {
        r.Background({0.4f, 0.4f, 0.4f, 0.4f});

        r.DrawCircle(300, 300, 100, {0.4, 0, 1, 0});

        r.SwapBuffers();

        r.PollEvents();
    }
}