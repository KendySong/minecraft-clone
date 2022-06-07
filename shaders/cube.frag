#version 330
in vec2 v_texUV;
in float v_texID;

out vec4 outputColor;

uniform sampler2D sampler[1];

void main()
{
    int samplerID = int(v_texID);
    outputColor = texture(sampler[samplerID], v_texUV);
}