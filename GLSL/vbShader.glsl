#version 400

uniform mat4    uProjView;
uniform mat4    modelMatrix;

uniform float   timer;
uniform float   frustum_cube;

in vec3         inPosition;             // Input vertex position
in vec3         iArray2;                // Input tex_coords
in vec2         iArray3;                // Input normals

out vec3        oArray2;                // texcoords out
out vec2        oArray3;                // normal out
out float       _timer;


void main() {
    vec3 a      = inPosition; 

    oArray2     = iArray2;
    oArray3     = iArray3;
    _timer      = timer;
    
    float cube_size = frustum_cube;

    gl_Position = uProjView * modelMatrix * vec4( a, 1.0);
}