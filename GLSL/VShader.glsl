#version 120


//uniform mat4	uProj_Matrix;
//uniform mat4	uView_Matrix;
uniform mat4	uProjView;
uniform float	PI;
uniform float	rotate_z;

vec3			a = vec3( gl_Vertex.x, gl_Vertex.y,  gl_Vertex.z);
vec3			b = a;

void main(){
	float rad_angle	=  rotate_z * PI/180.0;

	b.x = a.x*cos(rad_angle) + a.y*sin(rad_angle);
	b.y = a.y*cos(rad_angle) - a.x*sin(rad_angle);

//	mat4 Proj_View = uProj_Matrix * uView_Matrix;

	gl_Position =  uProjView *  vec4( b, 1.0 );
}
