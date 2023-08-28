#version 330

uniform mat4        uProjView;

in vec3             position;
in vec2             textureCoordinates;

out vec2            vTextureCoordinates;

void main() {
    gl_Position         = uProjView * vec4(position, 1.0);
    vTextureCoordinates = textureCoordinates;
}

