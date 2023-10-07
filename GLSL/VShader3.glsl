#version 400

uniform mat4	uProjView;

layout (packed) uniform _Coord {
    // float coord.data[8]; // 2048 elements
    vec2 data[4];
}coord;

in vec3     iArray1;                // Input vertex position

out vec2	_texCoords;
vec2		texCoordArray[4];



void main(){
    
    texCoordArray[0] = coord.data[0];//vec2( coord.coord.data[2], coord.coord.data[3]); 
    texCoordArray[1] = coord.data[1];//vec2( coord.coord.data[2], coord.coord.data[3]);
    texCoordArray[2] = coord.data[2];//vec2( coord.coord.data[4], coord.coord.data[5]);
    texCoordArray[3] = coord.data[3];//vec2( coord.coord.data[6], coord.coord.data[7]);

	_texCoords = texCoordArray[gl_VertexID];

	gl_Position =  uProjView * vec4( iArray1, 1.0 );
}