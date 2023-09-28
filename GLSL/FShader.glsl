#version 400

in vec4 fragColor;  // Input fragment color from the vertex shader

out vec4 finalColor;  // Output fragment color

void main() {
    finalColor = fragColor;
}