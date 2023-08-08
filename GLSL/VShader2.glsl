#version 120


uniform mat4	uProj_Matrix;
uniform mat4	uView_Matrix;
uniform mat4	uProjView;



vec3			a = vec3( gl_Vertex.x, gl_Vertex.y,  gl_Vertex.z);


void main(){

	gl_Position =  uProjView *  vec4( a, 1.0 );
}
