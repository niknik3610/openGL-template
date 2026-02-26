#version 330 core

out vec4 FragColor;
uniform float fragCol;

void main() {
    FragColor = vec4(0.0, 0.0, fragCol, 1.0);
}
