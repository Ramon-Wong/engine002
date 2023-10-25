#version 400


in  vec2               _texCoords;            // texcoords in
out vec4                fColor;
uniform sampler2D       tSampler; 


void main(){
    fColor = texture( tSampler, _texCoords);
}
