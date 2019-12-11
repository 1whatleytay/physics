#version 410

layout (location=0) out vec4 outColor;

in vec2 texCoordFrag;

uniform sampler2D tex;

void main() {
    outColor = texture(tex, texCoordFrag);
}
