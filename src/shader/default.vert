#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;


uniform mat4 transform;
uniform mat4 view;
uniform mat4 perspective;
out vec2 TexCoord;

void main()
{
    TexCoord = aTexCoord;
    gl_Position = perspective * view * transform * vec4(aPos, 1.0);
}
