#version 400

uniform mat4	uProjView;

layout (packed) uniform _Fontmap {
    vec2 data[1024];     
}coord;


in vec3     iArray1;                // Input vertex position

out vec2	_texCoords;
vec2		texCoordArray[4];

void main(){
    
    int instanceID = int(gl_InstanceID);
    int loc = (23 + instanceID) * 8;

    texCoordArray[0] = coord.data[loc+0] + vec2( 0.011, 0);
    texCoordArray[1] = coord.data[loc+1] - vec2( 0.011, 0); 
    texCoordArray[2] = coord.data[loc+2] - vec2( 0.011, 0);
    texCoordArray[3] = coord.data[loc+3] + vec2( 0.011, 0);;

	_texCoords = texCoordArray[gl_VertexID];

	gl_Position =  uProjView * vec4( iArray1.x - (instanceID * 0.125), iArray1.y, iArray1.z, 1.0 );
}