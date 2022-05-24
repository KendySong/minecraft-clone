#version 330
layout (location = 0) in vec3 verctice;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 texCoords;

void main()
{
    gl_Position = projection * view * model * vec4(verctice, 1);
}