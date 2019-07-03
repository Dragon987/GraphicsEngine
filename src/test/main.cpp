#include "./../engine.hpp"

#define uint unsigned int

int main()
{
    Renderer r("title", 640, 480);

    while (!r.WindowShouldClose())
    {
        r.Background({0.0f, 0.0f, 0.0f, 0.0f});

        r.DrawCircle(300, 300, 100, {1, 0, 0, 0});

        r.SwapBuffers();

        r.PollEvents();
    }
}