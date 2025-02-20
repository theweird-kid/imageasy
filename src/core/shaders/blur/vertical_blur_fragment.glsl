#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D image;
uniform float weight[5];
uniform float texOffsetY;

void main()
{
    vec3 result = texture(image, TexCoord).rgb * weight[0];
    for(int i = 1; i < 5; ++i)
    {
        result += texture(image, TexCoord + vec2(0.0, texOffsetY * i)).rgb * weight[i];
        result += texture(image, TexCoord - vec2(0.0, texOffsetY * i)).rgb * weight[i];
    }
    FragColor = vec4(result, 1.0);
}
