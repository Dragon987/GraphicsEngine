#shader vertex
#version 130

in vec4 pos;
in vec2 texCoord;

out vec2 fTexCoord;

uniform mat4 uProj;

void main()
{
    fTexCoord = texCoord;
    gl_Position = uProj * pos;// * uProj;
}

#shader fragment
#version 130

out vec4 color;
uniform sampler2D tex;

in vec2 fTexCoord;

uniform int useTextures;

uniform vec4 uColor;

void main()
{
    if (useTextures == 1)
        color = texture(tex, fTexCoord);
    else
        color = uColor;
}