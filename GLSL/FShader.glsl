#version 400

in vec3 _RGB;

void main(){
    gl_FragColor = vec4( _RGB, 1.0);
}
