#version 400

uniform mat4	uProjView;

in vec3     iArray1;                // Input vertex position
in vec2     iArray3;                // texcoords

out vec2	_texCoords;

void main(){

	_texCoords	= iArray3;
	gl_Position =  uProjView * vec4( iArray1, 1.0 );
}
