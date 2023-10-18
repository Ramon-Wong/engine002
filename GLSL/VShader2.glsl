#version 400


uniform mat4	uProjView;
uniform mat4	ModelMatrix;
uniform mat4	inverted;

in vec3     iArray1;                // Input vertex position
in vec3     iArray2;                // Input Colors
in vec2     iArray3;                // texcoords

out vec4	FragPos;
out vec4	ShadowCoord;

void main(){

	FragPos		=	ModelMatrix * vec4( iArray1, 1.0 );
	ShadowCoord =	uProjView	* FragPos;
	gl_Position =	uProjView	* FragPos;
}
