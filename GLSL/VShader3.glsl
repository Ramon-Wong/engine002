#version 400

uniform mat4	uProjView;

layout (std140) uniform DataCube {
    float data[2048]; // 2048 elements
};


in vec3     iArray1;                // Input vertex position

out vec2	_texCoords;
vec2		texCoordArray[4];



void main(){

    DataCube.data[0];

    texCoordArray[0] = vec2( 0.0, 0.0);
    texCoordArray[1] = vec2( 1.0, 0.0);
    texCoordArray[2] = vec2( 1.0, 1.0);
    texCoordArray[3] = vec2( 0.0, 1.0);

	_texCoords = texCoordArray[gl_VertexID];

	gl_Position =  uProjView * vec4( iArray1, 1.0 );
}