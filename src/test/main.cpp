#include "./../engine.hpp"

#include <iostream>
#include <chrono>

#define uint unsigned int

int main(int argc, char *argv[])
{
    Renderer r("title", 500, 500);

    double x = 10, y = 10;

    float a = 0.0f;
	r.StartClock();
	int fr = atoi(argv[1]);
    while (!r.WindowShouldClose())
    {
		auto start = std::chrono::system_clock::now();
        r.Background({0.0f, 0.0f, 0.0f, 0.0f});

        r.FillEllipse(350, 250, 100, 120, a, {1, 1, 1, 1});
        r.DrawCircle(250, 250, 100, {0, 1, 0, 1});

		r.FrameRate(fr);

        a += 0.01;

		auto end = std::chrono::system_clock::now();

		std::chrono::duration<float> el = end - start;

		// std::cout << el.count() << '\n';

        r.SPollEvents();
    }
}
