#version 400

uniform mat4 uProjView;

in vec3 inPosition;     // Input vertex position
in vec3 aColor;         // Input Colors
in vec2 texCoord;       // texcoords

out vec2 vTexCoord;     // texcoords out


void main() {
    vec3 a      = inPosition;
    vTexCoord   = texCoord;

    gl_Position = uProjView * vec4(a, 1.0);
}