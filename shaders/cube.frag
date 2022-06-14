#version 330
in vec2 v_texUV;
in float v_texID;

out vec4 outputColor;

uniform sampler2D sampler[3];

void main()
{
    int samplerID = int(v_texID);

	float lightStrengh = 0.0f;
    vec4 lighColor = vec4(1, 1, 1, 1);

	outputColor = mix(texture(sampler[samplerID], v_texUV), lighColor, lightStrengh);
    //outputColor = texture(sampler[samplerID], v_texUV) * vec4(0.5, 1, 1, 1);
}