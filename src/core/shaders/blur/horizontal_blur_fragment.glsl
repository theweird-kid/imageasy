#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D image;
uniform float weight[5];
uniform float texOffsetX;

void main()
{
    vec3 result = texture(image, TexCoord).rgb * weight[0];
    for(int i = 1; i < 5; ++i)
    {
        result += texture(image, TexCoord + vec2(texOffsetX * i, 0.0)).rgb * weight[i];
        result += texture(image, TexCoord - vec2(texOffsetX * i, 0.0)).rgb * weight[i];
    }
    FragColor = vec4(result, 1.0);
}
