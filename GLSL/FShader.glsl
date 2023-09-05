#version 400

in vec3             oArray2;            // texcoords out
in vec2             oArray3;            // texcoords out

out vec4            fColor;             // Output fragment color

uniform sampler2D   tSampler; 


void main() {

    fColor = texture( tSampler, oArray3);
}