#version 400

in vec2             vTexCoord;              // texcoords out

out vec4            fColor;            // Output fragment color

uniform sampler2D   tSampler; 


void main() {
    //fColor = fragColor;
    fColor = texture( tSampler, vTexCoord);
}