#version 400

in vec3             oArray2;            // colors in
in vec2             oArray3;            // texcoords in

out vec4            fColor;             // Output fragment color

uniform sampler2D   tSampler; 


void main() {

    fColor = texture( tSampler, oArray3);
}