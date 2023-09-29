#version 400


uniform mat4	uProjView;

uniform float	PI;
uniform float	rotate_z;
uniform mat4	ModelMatrix;

in vec3     iArray1;                // Input vertex position
in vec3     iArray2;                // Input Colors
in vec2     iArray3;                // texcoords

vec3			a = iArray1;
vec3			b = a;

void main(){
	float rad_angle	=  rotate_z * PI/180.0;

	b.x = a.x*cos(rad_angle) + a.y*sin(rad_angle);
	b.y = a.y*cos(rad_angle) - a.x*sin(rad_angle);

	gl_Position =  uProjView * ModelMatrix * vec4( b, 1.0 );
}
