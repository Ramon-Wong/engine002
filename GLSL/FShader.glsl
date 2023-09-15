#version 400

in vec3             oArray2;            // colors in
in vec2             oArray3;            // texcoords in

out vec4            fColor;             // Output fragment color

uniform sampler2D   tSampler; 
uniform sampler2D   sSampler; 

void main() {

    vec4 tex1   = texture( tSampler, oArray3);
    vec4 tex2   = texture( sSampler, oArray3);

    fColor  = tex1 * 0.5 + tex2 * 0.5;
}