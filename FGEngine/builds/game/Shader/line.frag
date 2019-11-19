#version 440 core


in vec2 TexCoord;
in vec3 Color;
out vec4 frag_color;

void main() {

    frag_color = vec4(Color, 1.0f);
}