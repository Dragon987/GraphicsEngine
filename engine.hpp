#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Color
{
    float r, g, b, a;
};




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
    int width, height;
    std::string title;

public:
    Renderer(const std::string &title, int width, int height);
    ~Renderer();

    inline bool WindowShouldClose() { return glfwWindowShouldClose(window); };
    inline void SwapBuffers() { glfwSwapBuffers(window); };
    inline void PollEvents() { glfwPollEvents(); };
    inline void SetShaderPath(const std::string &name) { shaderFile = name; };
    void MakeShader();

    void Background(Color c);
    void Translate(float left, float right, float bottom, float top, float near, float far);
    void Translate();
    void FillTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Color c);
    void Line(float x1, float y1, float x2, float y2, Color c);
    void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Color c);
    void FillRect(float x, float y, float w, float h, Color c);
    void DrawRect(float x, float y, float w, float h, Color c);
    void FillCircle(float x, float y, float radius, Color c);
    void DrawCircle(float x, float y, float radius, Color c);

};


