#version 400

uniform mat4	uProjView;




layout(packed) uniform Fontmap {
    float data[2048];
}coord;

layout(packed) uniform _Message {
    int data[32];
}msg;


in vec3     iArray1;                // Input vertex position

out vec2	_texCoords;
vec2		texCoordArray[4];



void main(){
    
    int loc = (msg.data[1]) * 8;

    
    texCoordArray[0] = vec2( coord.data[loc+0], coord.data[loc+1]); 
    texCoordArray[1] = vec2( coord.data[loc+2], coord.data[loc+3]);
    texCoordArray[2] = vec2( coord.data[loc+4], coord.data[loc+5]);
    texCoordArray[3] = vec2( coord.data[loc+6], coord.data[loc+7]);

	_texCoords = texCoordArray[gl_VertexID];

	gl_Position =  uProjView * vec4( iArray1, 1.0 );
}