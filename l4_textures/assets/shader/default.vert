#version 330 core

in vec3 position;
in vec3 color;
in vec2 textureCoordinate;

out vec3 ourColor;
out vec2 fragTextureCoordinate;

void main() {
    gl_Position = vec4(position.x, position.y, position.z, 1.0f);
    ourColor = color;
    fragTextureCoordinate = textureCoordinate;
}