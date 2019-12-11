#version 410

layout (location=0) in vec2 position;
layout (location=1) in vec2 texCoord;

out vec2 texCoordFrag;

uniform vec2 screenSize;
uniform vec2 offset;

void main() {
    texCoordFrag = texCoord;
    vec2 real = position + offset;

    gl_Position = vec4(real.x / screenSize.x * 2 - 1, -(real.y / screenSize.y * 2 - 1), 0, 1);
}
