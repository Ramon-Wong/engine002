#version 330 core

out vec4    fragment;
in  vec3    vColor;

void main() {
    fragment = vec4( vColor, 1.0);
}