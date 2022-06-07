#version 330
in vec2 textureCoordinates;

out vec4 outputColor;

uniform sampler2D sampler;

void main()
{
    outputColor = texture(sampler, textureCoordinates);
}