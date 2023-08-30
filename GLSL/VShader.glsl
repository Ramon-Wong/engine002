#version 330 core

uniform mat4 uProjView;

in vec3    aPos;
in vec3    aColor;

out vec3    vColor;

void main() {
    gl_Position     = uProjView * vec4( aPos, 1.0);
    vColor          = vec3( aColor.x, 1.0, 1.0);
}
