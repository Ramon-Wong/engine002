#version 400

in vec4             fragColor;              // Input fragment color from the vertex shader
in vec2             vTexCoord;              // texcoords out

out vec4            fColor;            // Output fragment color

uniform sampler2D   tSampler; 


void main() {
    //fColor = fragColor;
    fColor = texture( tSampler, vTexCoord);
}