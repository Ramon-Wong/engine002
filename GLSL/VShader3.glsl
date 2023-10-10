#version 400

uniform mat4	uProjView;


layout(packed) uniform Fontmap {
    float data[2048];
}coord;

layout(packed) uniform _Message {
    int data[64];
}msg;


in vec3     iArray1;                // Input vertex position

out vec2	_texCoords;
vec2		texCoordArray[4];



void main(){

    int instanceID = int(gl_InstanceID);

    if( msg.data[gl_InstanceID] >= 0){

        int loc = (msg.data[gl_InstanceID]) * 8;

        texCoordArray[0] = vec2( coord.data[loc+0], coord.data[loc+1]); 
        texCoordArray[1] = vec2( coord.data[loc+2], coord.data[loc+3]);
        texCoordArray[2] = vec2( coord.data[loc+4], coord.data[loc+5]);
        texCoordArray[3] = vec2( coord.data[loc+6], coord.data[loc+7]);

        _texCoords = texCoordArray[gl_VertexID];

	    gl_Position =  uProjView * vec4( iArray1.x - (instanceID * 0.15), iArray1.y, iArray1.z, 1.0 );
    }
}