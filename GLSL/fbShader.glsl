#version 400

in vec2             oArray2;            // colors in
out vec4            fColor;             // Output fragment color

uniform sampler2D   tSampler; 

void main() {
    fColor = texture( tSampler, oArray2);
}