#version 400

uniform mat4	ViewProj_Matrix;
in vec3 vp;


void main(){
    gl_Position = ViewProj_Matrix * vec4(vp, 1.0);
}