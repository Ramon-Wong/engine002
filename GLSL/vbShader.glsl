#version 400

uniform mat4    uProjView;
uniform mat4    modelMatrix;

uniform float   timer;
uniform float   frustum_cube;

in vec3         inPosition;             // Input vertex position
in vec3         iArray2;                // Input Normals    ( really ?)
in vec2         iArray3;                // Input Texcoords  ( really ?)

out vec3        oArray2;                // Normals      out
out vec2        oArray3;                // TexCoords    out
out float       _timer;


void main() {
    vec3 a          = inPosition; 

    // vec4 nNormal    = (modelMatrix * vec4(iArray2, 1.0));
    vec4 transformedNormal = transpose( inverse(modelMatrix)) * vec4( iArray2, 0.0);
    vec3 transformedNormal3 = normalize(transformedNormal.xyz);

    oArray2         = transformedNormal3;
    oArray3         = iArray3;
    _timer          = timer;
    
    float cube_size = frustum_cube;

    vec4 target     = uProjView * modelMatrix * vec4( a, 1.0);

    gl_Position = target;
}