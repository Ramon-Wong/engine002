#version 400

uniform mat4	uProjView;

layout (packed) uniform _Fontmap {
    vec2 data[1024];     
}coord;

in vec3     iArray1;                // Input vertex position

out vec2	_texCoords;
vec2		texCoordArray[4];

void main(){
    
    int loc = 35 * 8;

    texCoordArray[0] = coord.data[loc+0];
    texCoordArray[1] = coord.data[loc+1]; 
    texCoordArray[2] = coord.data[loc+2];
    texCoordArray[3] = coord.data[loc+3];

	_texCoords = texCoordArray[gl_VertexID];

	gl_Position =  uProjView * vec4( iArray1, 1.0 );
}