#version 410 core

in vec3 ourColor;
in vec2 TextureCoordinates;

out vec4 color;

uniform sampler2D ourTexture;

void main() {
    color = texture(ourTexture, TextureCoordinates) * vec4(ourColor, 1.0f);
}