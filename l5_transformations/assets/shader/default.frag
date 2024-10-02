#version 330 core

in vec2 fragTextureCoordinate;

out vec4 fragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main() {
    fragColor = mix(texture(texture0, fragTextureCoordinate),
                    texture(texture1, fragTextureCoordinate), 0.2);
}