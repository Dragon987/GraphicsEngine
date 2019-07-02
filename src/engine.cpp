#include <iostream>
#include <fstream>
#include <sstream>

#include "./engine.hpp"

static unsigned int CompileShader(unsigned int type, const std::string &src)
{
    unsigned int id = glCreateShader(type);
    const char *s = src.c_str();
    glShaderSource(id, 1, &s, nullptr);

    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int l;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &l);
        char *msg = (char*)alloca(l * sizeof(char));
        glGetShaderInfoLog(id, l, &l, msg);
        std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!\n";
        std::cerr << msg << "\n";
        glDeleteShader(id);
        return 0;
    }
    return id;
}

struct ShaderSource
{
    unsigned int v, f;
};


static ShaderSource ParseShader(const std::string &filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    ShaderType mode = ShaderType::NONE;

    std::string line;
    std::stringstream ss[2];

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                mode = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                mode = ShaderType::FRAGMENT;
        }
        else
        {
            if (mode != ShaderType::NONE)
                ss[(int)mode] << line << "\n";
        }
    }

    // std::cout << ss[0].str() << "---------------------------------\n";
    // std::cout << ss[1].str() << "---------------------------------\n";
    stream.close();
    return {
        CompileShader(GL_VERTEX_SHADER, ss[0].str()), 
        CompileShader(GL_FRAGMENT_SHADER, ss[1].str())
    };
}

void Renderer::MakeShader()
{
    auto ss = ParseShader(shaderFile);

    shader = glCreateProgram();

    glAttachShader(shader, ss.v);
    glAttachShader(shader, ss.f);
    glLinkProgram(shader);

    GLint program_linked;
    glGetProgramiv(shader, GL_LINK_STATUS, &program_linked);
    if (program_linked != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetProgramInfoLog(shader, 1024, &log_length, message);
        std::cerr << "Could not link program! [Error] > " << message << "\n";
    }

}


Renderer::Renderer(const std::string &title, int width, int height)
                    : title(title), width(width), height(height)
{
    if (!glfwInit())
    {
        std::cerr << "GLFW failed!\n";
        std::cin.get();
        exit(-1);
    }

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!window)
    {
        std::cerr << "GLFW window failed!\n";
        std::cin.get();
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "GLEW failed!\n";
        std::cin.get();
        exit(-1);
    }
    projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 0.0f, 1.0f);
    MakeShader();
}

void Renderer::Uniform4f(const std::string &name, float r, float g, float b, float a)
{
    int loc = GetUniformLocation(name);

    glUniform4f(loc, r, g, b, a);
}



void Renderer::FillTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Color c)
{
    float positions[] = {
        x1, y1,
        x2, y2,
        x3, y3
    };

    unsigned int vb;

    glCreateBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);

    glBufferData(GL_ARRAY_BUFFER, 24, positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, nullptr);

    glUseProgram(shader);
    Uniform4f("col", c.r, c.g, c.b, c.a);
    Matrix4("uProj");

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vb);
}

Renderer::~Renderer()
{
    glDeleteProgram(shader);
    glfwTerminate();
}

void Renderer::Background(Color c)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(c.r, c.g, c.b, c.a);
}

void Renderer::Matrix4(const std::string name)
{
    int loc = GetUniformLocation(name);

    glUniformMatrix4fv(loc, 1, GL_FALSE, &projection[0][0]);
}

void Renderer::Line(float x1, float y1, float x2, float y2, Color c)
{
    float positions[] = {
        x1, y1,
        x2, y2
    };

    unsigned int vb;

    glCreateBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);

    glBufferData(GL_ARRAY_BUFFER, 16, positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, nullptr);

    glUseProgram(shader);
    Uniform4f("col", c.r, c.g, c.b, c.a);
    Matrix4("uProj");

    glDrawArrays(GL_LINES, 0, 2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vb);
}

void Renderer::Translate(float left, float right, float bottom, float top, float near, float far)
{
    projection = glm::ortho(left, right, bottom, top, near, far);
}

void Renderer::Translate()
{
    projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 0.0f, 1.0f);
}

void Renderer::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Color c)
{
    Line(x1, y1, x2, y2, c);
    Line(x1, y1, x3, y3, c);
    Line(x3, y3, x2, y2, c);
}

void Renderer::FillRect(float x, float y, float w, float h, Color c)
{
    unsigned int vb, ib;

    float positions[] = {
        x,     y,
        x + w, y,
        x + w, y + h,
        x,     y + h,
    };

    unsigned int indices[]
    {
        0, 1, 2, 0, 3, 2
    };

    glGenBuffers(1, &vb);
    glGenBuffers(1, &ib);

    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, 32, positions, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24, indices, GL_STATIC_DRAW);

    glUseProgram(shader);
    Uniform4f("col", c.r, c.g, c.b, c.a);
    Matrix4("uProj");

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, nullptr);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vb);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &ib);
}

void Renderer::DrawRect(float x, float y, float w, float h, Color c)
{
    Line(x    , y    , x + w, y    , c);
    Line(x + w, y    , x + w, y + h, c);
    Line(x + w, y + h, x    , y + h, c);
    Line(x    , y + h, x    , y    , c);
}


void Renderer::FillCircle(float x, float y, float radius, Color c)
{
    int numberOfSides = 1000;
    int numberOfVertices = numberOfSides + 2;
    
    float twicePi = 2.0f * 3.14159f;
    
    float circleVerticesX[numberOfVertices];
    float circleVerticesY[numberOfVertices];
    
    circleVerticesX[0] = x;
    circleVerticesY[0] = y;
    
    for ( int i = 1; i < numberOfVertices; i++ )
    {
        circleVerticesX[i] = x + ( radius * cos( i *  twicePi / numberOfSides ) );
        circleVerticesY[i] = y + ( radius * sin( i * twicePi / numberOfSides ) );
    }
    
    float allCircleVertices[numberOfVertices * 2];
    
    for ( int i = 0; i < numberOfVertices; i++ )
    {
        allCircleVertices[i * 2] = circleVerticesX[i];
        allCircleVertices[i * 2 + 1] = circleVerticesY[i];
    }
    
    unsigned int vb;

    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(allCircleVertices), allCircleVertices, GL_STATIC_DRAW);

    glUseProgram(shader);
    Uniform4f("col", c.r, c.g, c.b, c.a);
    Matrix4("uProj");

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, nullptr);

    glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vb);
}


void Renderer::DrawCircle(float x, float y, float radius, Color c)
{
    int numberOfSides = 1000;
    int numberOfVertices = numberOfSides + 2;
    
    float twicePi = 2.0f * 3.14159f;
    
    float circleVerticesX[numberOfVertices];
    float circleVerticesY[numberOfVertices];
    
    circleVerticesX[0] = x;
    circleVerticesY[0] = y;

    circleVerticesX[1] = x + ( radius * cos( 1 *  twicePi / numberOfSides ) );
    circleVerticesY[1] = y + ( radius * sin( 1 * twicePi / numberOfSides ) );
    
    for ( int i = 2; i < numberOfVertices; i++ )
    {
        circleVerticesX[i] = x + ( radius * cos( i *  twicePi / numberOfSides ) );
        circleVerticesY[i] = y + ( radius * sin( i * twicePi / numberOfSides ) );

        Line(circleVerticesX[i - 1], circleVerticesY[i - 1], 
             circleVerticesX[i]    , circleVerticesY[i], c);
    }
}