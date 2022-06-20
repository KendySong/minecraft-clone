#version 450 core
in vec2 v_texUV;
in float v_texID;

in vec3 v_normal;
in vec3 v_fragPosition;

uniform vec3 lightPosition;
uniform sampler2D textureSampler[5];

out vec4 outputColor;

void main()
{
    //Calculate light direction
    vec3 normalizeSurface = normalize(v_normal);
    vec3 lightDirection = normalize(lightPosition - v_fragPosition);

    //Calculate light color on fragment
    vec3 lightColor = vec3(0.8, 0.8, 0.8);
    float difference = max(dot(normalizeSurface, lightDirection), 0);
    vec3 diffuse = difference * lightColor;

    //Set texture with ligth
    outputColor = vec4((lightColor + diffuse) * texture(textureSampler[int(v_texID)], v_texUV).xyz, 1);
}