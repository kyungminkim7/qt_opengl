#version 330 core

in vec3 position;
in vec2 textureCoordinate;

out vec2 fragTextureCoordinate;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(position.x, position.y, position.z, 1.0f);
    fragTextureCoordinate = textureCoordinate;
}