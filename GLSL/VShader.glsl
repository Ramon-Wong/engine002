#version 330

uniform mat4 uProjView;

in vec3 inPosition;  // Input vertex position


void main() {
    gl_Position     = uProjView * vec4( inPosition, 1.0);
}