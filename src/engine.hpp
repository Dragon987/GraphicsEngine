#pragma once


#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Color
{
    float r, g, b, a;
};

#define DRAW_MODE_LINES GL_LINES
#define DRAW_MODE_LINE_STRIP GL_LINE_STRIP
#define DRAW_MODE_LINE_LOOP GL_LINE_LOOP
#define DRAW_MODE_TRIANGLE_STRIP GL_TRIANGLE_STRIP
#define DRAW_MODE_TRIANGLE_FAN GL_TRIANGLE_FAN

typedef GLenum drawEnum;


class Renderer
{
private:
    GLFWwindow *window;
    unsigned int shader;
    std::string shaderFile = "/usr/include/shaders/Main.glsl";
    glm::mat4 projection;

private:
    inline int GetUniformLocation(const std::string &name) { return glGetUniformLocation(shader, name.c_str()); };
    void Uniform4f(const std::string &name, float r, float g, float b, float a);
    void Matrix4(std::string name);

public:
    int width, height, depth;
    std::string title;

    enum RectMode
    {
        RECT_MODE_CENTER, RECT_MODE_TOP_LEFT
    };

public:
    Renderer(const std::string &title, int width, int height);
    ~Renderer();

    inline bool WindowShouldClose() { return glfwWindowShouldClose(window); };
    inline void SwapBuffers() { glfwSwapBuffers(window); };
    inline void PollEvents() { glfwPollEvents(); };

    inline void SetShaderPath(const std::string &name) { shaderFile = name; };
    void MakeShader();

    inline void BeginDraw(drawEnum mode) { glBegin(mode); };
    inline void Vertex(float x, float y) { glVertex2f(x, y); };
    inline void Vertex(float x, float y, float z) { glVertex3f(x, y, z); };
    inline void EndDraw() { glEnd(); };
    inline void Fill(Color c) { glColor4f(c.r, c.g, c.b, c.a); };

    void Background(Color c);

    void Translate(float left, float right, float bottom, float top, float near, float far);
    void Translate();

    void Line(float x1, float y1, float x2, float y2, Color c);

    void FillTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Color c);
    void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Color c);

    void FillRect(float x, float y, float w, float h, RectMode mode, Color c);
    void DrawRect(float x, float y, float w, float h, RectMode mode, Color c);
    
    void FillCircle(float x, float y, float radius, Color c);
    void DrawCircle(float x, float y, float radius, Color c);

};


