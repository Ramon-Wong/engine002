#version 400

uniform mat4    uProjView;
uniform float   rotate_z;

uniform mat4    modelMatrix;



in vec3         inPosition;             // Input vertex position
in vec3         iArray2;                // Input Colors
in vec3         iArray3;                // Input normals

out vec3        oArray2;                // Color out



void main() {
    vec3 a      = inPosition; 
    vec3 b      = a;

    oArray2     = iArray2;

    gl_Position = uProjView * modelMatrix * vec4( b, 1.0);
}