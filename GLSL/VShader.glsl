#version 400

uniform mat4 uProjView;

in vec3     inPosition;             // Input vertex position
in vec3     aColor;                 // Input Colors
in vec2     iArray3;                // texcoords

out vec3    oArray2;                // Color out
out vec2    oArray3;                // texcoords out


void main() {
    vec3 a      = inPosition; 
    oArray3     = iArray3;
    oArray2     = aColor;    

    gl_Position = uProjView * vec4(a, 1.0);
}