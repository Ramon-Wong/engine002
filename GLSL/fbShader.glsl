#version 400

in vec3             oArray2;            // texcoords
in vec2             oArray3;            // normals 

out vec4            fColor;             // Output fragment color

uniform sampler2D   tSampler; 

void main() {
    fColor = texture( tSampler, oArray3);
}