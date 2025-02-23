#version 460

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout(binding = 0) uniform sampler2D inputTexture;
layout(binding = 1, rgba32f) uniform image2D outputTexture;

uniform float contrastFactor;

void main() {
    ivec2 pixelCoords = ivec2(gl_GlobalInvocationID.xy);
    vec4 color = texelFetch(inputTexture, pixelCoords, 0);

    // Adjust contrast
    color.rgb = ((color.rgb - 0.5) * contrastFactor) + 0.5;

    imageStore(outputTexture, pixelCoords, color);
}
