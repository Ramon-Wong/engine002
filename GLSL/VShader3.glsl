#version 400

uniform mat4	uProjView;

in vec3     iArray1;                // Input vertex position
in vec2     iArray3;                // texcoords

out vec2	_texCoords;
vec2		texCoordArray[4];

layout (std140) uniform DataBlock {
    float RadiusInner;
    float RadiusOuter;
};


// layout(location = 0) buffer DataBlock{
//     float data[2048];
// };

// layout (binding = 0) buffer DataBlock;

// layout (location = 0) buffer DataBlock;

void main(){

    texCoordArray[0] = vec2(0.0, 0.0);
    texCoordArray[1] = vec2(1.0, 0.0);
    texCoordArray[2] = vec2(1.0, 1.0);
    texCoordArray[3] = vec2(0.0, 1.0);

	_texCoords = texCoordArray[gl_VertexID];

	gl_Position =  uProjView * vec4( iArray1, 1.0 );
}