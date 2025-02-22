#version 460 core

layout (local_size_x = 16, local_size_y = 16) in;

// Input and output images
layout (binding = 0, rgba32f) uniform image2D inputImage;
layout (binding = 1, rgba32f) uniform image2D outputImage;

// Gaussian weights for a 5x5 kernel
const float weights[5] = float[](0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main() {
    ivec2 pixelCoords = ivec2(gl_GlobalInvocationID.xy);
    ivec2 imageSize = imageSize(inputImage);

    // Horizontal blur
    vec4 color = vec4(0.0);
    for (int i = -4; i <= 4; ++i) {
        int x = clamp(pixelCoords.x + i, 0, imageSize.x - 1);
        color += imageLoad(inputImage, ivec2(x, pixelCoords.y)) * weights[abs(i)];
    }

    // Store the horizontally blurred result in the output image
    imageStore(outputImage, pixelCoords, color);
}
