#version 330
layout (location = 0) in vec3 verctice;

uniform mat4 projection;
uniform mat4 view;

uniform vec3 positions[100];

void main()
{
    gl_Position = projection * view * vec4(verctice + positions[gl_InstanceID], 1);
}