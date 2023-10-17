#version 400

uniform sampler2D tSampler;

in vec4 FragPos;
in vec4 ShadowCoord;

void main(){

    float fDepth        = FragPos.z / FragPos.w;
    float shadowDepth   = texture(tSampler, ShadowCoord.xy).r;

    shadowDepth = shadowDepth - 0.5;


    if (fDepth > shadowDepth) {
        gl_FragColor = vec4( 0.0, 0.0, 0.0, 1.0);
    } else {
        gl_FragColor = vec4( 1.0, 1.0, 1.0, 1.0);
    }    

    // gl_FragColor = vec4( 1.0, 1.0, 1.0, 1.0);
}
