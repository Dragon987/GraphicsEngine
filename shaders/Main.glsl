#shader vertex
#version 330 core

in vec4 pos;

uniform mat4 uProj;

void main()
{
    gl_Position = uProj * pos;
}

#shader fragment
#version 330 core

uniform vec4 col;
out vec4 color;

void main()
{
    color = col;
}
