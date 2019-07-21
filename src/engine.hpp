#pragma once

#include <vector>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define KEY_UNKNOWN            -1

/* Printable keys */
#define KEY_SPACE              32
#define KEY_APOSTROPHE         39  /* ' */
#define KEY_COMMA              44  /* , */
#define KEY_MINUS              45  /* - */
#define KEY_PERIOD             46  /* . */
#define KEY_SLASH              47  /* / */
#define KEY_0                  48
#define KEY_1                  49
#define KEY_2                  50
#define KEY_3                  51
#define KEY_4                  52
#define KEY_5                  53
#define KEY_6                  54
#define KEY_7                  55
#define KEY_8                  56
#define KEY_9                  57
#define KEY_SEMICOLON          59  /* ; */
#define KEY_EQUAL              61  /* = */
#define KEY_A                  65
#define KEY_B                  66
#define KEY_C                  67
#define KEY_D                  68
#define KEY_E                  69
#define KEY_F                  70
#define KEY_G                  71
#define KEY_H                  72
#define KEY_I                  73
#define KEY_J                  74
#define KEY_K                  75
#define KEY_L                  76
#define KEY_M                  77
#define KEY_N                  78
#define KEY_O                  79
#define KEY_P                  80
#define KEY_Q                  81
#define KEY_R                  82
#define KEY_S                  83
#define KEY_T                  84
#define KEY_U                  85
#define KEY_V                  86
#define KEY_W                  87
#define KEY_X                  88
#define KEY_Y                  89
#define KEY_Z                  90
#define KEY_LEFT_BRACKET       91  /* [ */
#define KEY_BACKSLASH          92  /* \ */
#define KEY_RIGHT_BRACKET      93  /* ] */
#define KEY_GRAVE_ACCENT       96  /* ` */
#define KEY_WORLD_1            161 /* non-US #1 */
#define KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define KEY_ESCAPE             256
#define KEY_ENTER              257
#define KEY_TAB                258
#define KEY_BACKSPACE          259
#define KEY_INSERT             260
#define KEY_DELETE             261
#define KEY_RIGHT              262
#define KEY_LEFT               263
#define KEY_DOWN               264
#define KEY_UP                 265
#define KEY_PAGE_UP            266
#define KEY_PAGE_DOWN          267
#define KEY_HOME               268
#define KEY_END                269
#define KEY_CAPS_LOCK          280
#define KEY_SCROLL_LOCK        281
#define KEY_NUM_LOCK           282
#define KEY_PRINT_SCREEN       283
#define KEY_PAUSE              284
#define KEY_F1                 290
#define KEY_F2                 291
#define KEY_F3                 292
#define KEY_F4                 293
#define KEY_F5                 294
#define KEY_F6                 295
#define KEY_F7                 296
#define KEY_F8                 297
#define KEY_F9                 298
#define KEY_F10                299
#define KEY_F11                300
#define KEY_F12                301
#define KEY_F13                302
#define KEY_F14                303
#define KEY_F15                304
#define KEY_F16                305
#define KEY_F17                306
#define KEY_F18                307
#define KEY_F19                308
#define KEY_F20                309
#define KEY_F21                310
#define KEY_F22                311
#define KEY_F23                312
#define KEY_F24                313
#define KEY_F25                314
#define KEY_KP_0               320
#define KEY_KP_1               321
#define KEY_KP_2               322
#define KEY_KP_3               323
#define KEY_KP_4               324
#define KEY_KP_5               325
#define KEY_KP_6               326
#define KEY_KP_7               327
#define KEY_KP_8               328
#define KEY_KP_9               329
#define KEY_KP_DECIMAL         330
#define KEY_KP_DIVIDE          331
#define KEY_KP_MULTIPLY        332
#define KEY_KP_SUBTRACT        333
#define KEY_KP_ADD             334
#define KEY_KP_ENTER           335
#define KEY_KP_EQUAL           336
#define KEY_LEFT_SHIFT         340
#define KEY_LEFT_CONTROL       341
#define KEY_LEFT_ALT           342
#define KEY_LEFT_SUPER         343
#define KEY_RIGHT_SHIFT        344
#define KEY_RIGHT_CONTROL      345
#define KEY_RIGHT_ALT          346
#define KEY_RIGHT_SUPER        347
#define KEY_MENU               348

#define KEY_LAST               KEY_MENU

#define MOUSE_BUTTON_1         0
#define MOUSE_BUTTON_2         1
#define MOUSE_BUTTON_3         2
#define MOUSE_BUTTON_4         3
#define MOUSE_BUTTON_5         4
#define MOUSE_BUTTON_6         5
#define MOUSE_BUTTON_7         6
#define MOUSE_BUTTON_8         7
#define MOUSE_BUTTON_LAST      MOUSE_BUTTON_8
#define MOUSE_BUTTON_LEFT      MOUSE_BUTTON_1
#define MOUSE_BUTTON_RIGHT     MOUSE_BUTTON_2
#define MOUSE_BUTTON_MIDDLE    MOUSE_BUTTON_3

#define KEY_RELEASE                0
#define KEY_PRESS                  1
#define KEY_REPEAT                 2

struct Color
{
    float r, g, b, a;
};

#define DRAW_MODE_LINES GL_LINES
#define DRAW_MODE_LINE_STRIP GL_LINE_STRIP
#define DRAW_MODE_LINE_LOOP GL_LINE_LOOP
#define DRAW_MODE_TRIANGLE_STRIP GL_TRIANGLE_STRIP
#define DRAW_MODE_TRIANGLE_FAN GL_TRIANGLE_FAN
#define DRAW_MODE_TRIANGLES GL_TRIANGLES

typedef GLenum drawEnum;


class Renderer
{
private:
    GLFWwindow *window;
    unsigned int shader;
    std::string shaderFile = "/usr/include/shaders/Main.glsl";
    glm::mat4 projection;
    drawEnum drawMode;
    std::vector<float> drawPositions;
    Color drawColor = { 1, 1, 1, 1 };

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
    void SPollEvents();

    inline void SwapBuffers() { glfwSwapBuffers(window); };
    inline void PollEvents() { glfwPollEvents(); };

    inline void SetShaderPath(const std::string &name) { shaderFile = name; };
    void MakeShader();

    void BeginDraw(drawEnum mode);
    void Vertex(float x, float y);
    void EndDraw();
    void Fill(Color c);

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

    void GetMousePos(double *x, double *y);
    inline int GetKey(int key) { return glfwGetKey(window, key); };
    inline int GetMouseButton(int button) { return glfwGetMouseButton(window, button); };
};


