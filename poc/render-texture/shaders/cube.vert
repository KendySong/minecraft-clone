#version 330
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 uv;

out vec2 textureCoordinates;

void main()
{
	textureCoordinates = uv;
    gl_Position = vec4(vertex, 1);
}