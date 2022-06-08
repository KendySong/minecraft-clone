#version 330
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 texUV;
layout (location = 2) in float texID;

out vec2 v_texUV;
out float v_texID;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    v_texUV = texUV;
    v_texID = texID;
    gl_Position = projection * view * vec4(vertex, 1);
}