#version 330
layout (location = 0) in vec3 vertex;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * model * vec4(vertex, 1);  
}

/*
#version 330
layout (location = 0) in vec3 vertex;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * model * vec4(vertex, 1);
}
*/