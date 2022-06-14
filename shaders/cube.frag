#version 330
in vec2 v_texUV;
in float v_texID;

in vec3 v_normal;
in vec3 v_fragPosition;

uniform vec3 lightPosition;
uniform sampler2D sampler[3];

out vec4 outputColor;

void main()
{
    int samplerID = int(v_texID);
    outputColor = texture(sampler[samplerID], v_texUV);

    //Calculate direction between light and fragment
    vec3 normalizeSurface = normalize(v_normal);
    vec3 lightDirection = normalize(lightPosition - v_fragPosition);

    vec3 lightColor = vec3(1, 1, 1);
    float difference = max(dot(normalizeSurface, lightDirection), 0.0);
    vec3 diffuse = difference * lightColor;

    vec3 result = (lightColor + diffuse) * texture(sampler[samplerID], v_texUV).xyz;
    outputColor = vec4(result, 1.0);

/*  //Basic light
	float lightStrengh = 0.0f;
    vec4 lighColor = vec4(1, 1, 1, 1);
	outputColor = mix(texture(sampler[samplerID], v_texUV), lighColor, lightStrengh);
*/   
}