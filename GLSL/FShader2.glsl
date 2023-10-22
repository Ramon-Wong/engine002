#version 400

uniform sampler2D tSampler;

in vec4 FragPos;
in vec4 ShadowCoord;

void main(){

    float fDepth        = FragPos.z / (FragPos.w * 50.0 );

    vec2 nCoord         = ShadowCoord.xy;
    float shadowDepth   = texture(tSampler, nCoord).r;

    // shadowDepth = shadowDepth;

    shadowDepth = 1.0 - (1.0 - shadowDepth) * 25.0;

    gl_FragColor = vec4( shadowDepth);

    // if (fDepth - 0.0 > shadowDepth) {
    //     gl_FragColor = vec4( 0.5, 0.5, 0.5, 1.0);
    // } else {
    //     gl_FragColor = vec4( 1.0, 1.0, 1.0, 1.0);
    // }    

    
    // gl_FragColor = vec4( 1.0, 1.0, 1.0, 1.0);
}
