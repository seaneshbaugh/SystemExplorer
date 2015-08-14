#version 410 core

#define PI 3.1415926535897932384626433832795

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textureCoordinates;

out vec3 ourColor;

out vec2 TextureCoordinates;

uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

vec3 transformHue(vec3 rgb, float hue) {
    vec3 result;

    float cosA = cos(hue * PI / 180.0);

    float sinA = sin(hue * PI / 180.0);

    mat3 matrix = mat3(cosA + (1.0 - cosA) / 3.0,
                       1.0 / 3.0 * (1.0 - cosA) - sqrt(1.0 / 3.0) * sinA,
                       1.0 / 3.0 * (1.0 - cosA) + sqrt(1.0 / 3.0) * sinA,

                       1.0 / 3.0 * (1.0 - cosA) + sqrt(1.0 / 3.0) * sinA,
                       cosA + 1.0 / 3.0 * (1.0 - cosA),
                       1.0 / 3.0 * (1.0 - cosA) - sqrt(1.0 / 3.0) * sinA,

                       1.0 / 3.0 * (1.0 - cosA) - sqrt(1.0 / 3.0) * sinA,
                       1.0 / 3.0 * (1.0 - cosA) + sqrt(1.0 / 3.0) * sinA,
                       cosA + 1.0 / 3.0 * (1.0 - cosA));

    result.x = clamp(rgb.x * matrix[0][0] + rgb.y * matrix[0][1] + rgb.z * matrix[0][2], 0.0, 1.0);

    result.y = clamp(rgb.x * matrix[1][0] + rgb.y * matrix[1][1] + rgb.z * matrix[1][2], 0.0, 1.0);

    result.z = clamp(rgb.x * matrix[2][0] + rgb.y * matrix[2][1] + rgb.z * matrix[2][2], 0.0, 1.0);

    return result;
}

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0f);

    ourColor = transformHue(color, sin(time) * 360.0);

    TextureCoordinates = textureCoordinates;
}