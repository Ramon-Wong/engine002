#version 400

uniform mat4	uProjView;
uniform vec3	RGB;

in vec3     iArray1;                // Input vertex position
in vec3     iArray2;                // Input Colors
in vec2     iArray3;                // texcoords

out vec3	_RGB;

void main(){

	_RGB = RGB;
	gl_Position =  uProjView * vec4( iArray1, 1.0 );
}
