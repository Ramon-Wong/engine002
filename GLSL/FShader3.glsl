#version 400


in  vec3               _RGB;
in  vec2               _texCoords;            // texcoords in
out vec4                fColor;
uniform sampler2D       tSampler; 


void main(){
    // gl_FragColor = vec4( _RGB, 1.0);
    fColor = texture( tSampler, _texCoords);
}
