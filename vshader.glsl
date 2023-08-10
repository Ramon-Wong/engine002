#version 400
in vec3 vp;
uniform mat4	ViewProj_Matrix;

void main(){
    gl_Position = ViewProj_Matrix * vec4(vp, 1.0);
}