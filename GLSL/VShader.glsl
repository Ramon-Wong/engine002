#version 400

uniform mat4        uProjView;
uniform float       PI;
uniform float       rotate_z;

in vec3 inPosition;  // Input vertex position
in vec2 inTexCoord;

out vec2 texCoord;

void main() {

    gl_Position     = uProjView * vec4( inPosition, 1.0);
    texCoord        = inTexCoord;
}