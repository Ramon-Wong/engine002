#version 400

uniform mat4    uProjView;
uniform mat4    modelMatrix;

uniform float   timer;
uniform float   frustum_cube;

in vec3         inPosition;             // Input vertex position
in vec3         iArray2;                // Input tex_coords
in vec2         iArray3;                // Input normals

out vec3        oArray2;                // texcoords out
out vec2        oArray3;                // normal out
out float       _timer;

vec4            plane[6];                       // planes, left, right, bottom, top, near and far


void SetupPlanes(){
    plane[0] = uProjView[3] + uProjView[0];     // Left Plane
    plane[1] = uProjView[3] - uProjView[0];     // Right Plane
    plane[2] = uProjView[3] + uProjView[1];     // Bottom Plane
    plane[3] = uProjView[3] - uProjView[1];     // Top Plane
    plane[4] = uProjView[3] + uProjView[2];     // Near Plane
    plane[5] = uProjView[3] - uProjView[2];     // Far Plane
}

float frustum_culling(vec4 point){
    float       dotSum = 0.0f;
    
    for(int i = 0; i < 6; i++){
        dotSum += dot(plane[i], point);
    }

    return dotSum;
}

void main() {
    vec3 a      = inPosition; 
    vec3 b      = a;

    oArray2     = iArray2;
    oArray3     = iArray3;
    _timer      = timer;

    SetupPlanes();
    gl_Position = uProjView * modelMatrix * vec4( b, 1.0);
    
    // float cube_size = frustum_cube;

    // // frustum culling test
    // if( cube_size > 0.0){
    //     vec3    cube[8];

    //     float   sum = 0.0;

    //     cube[0] = vec3( -cube_size, cube_size, cube_size);
    //     cube[1] = vec3(  cube_size, cube_size, cube_size);
    //     cube[2] = vec3(  cube_size,-cube_size, cube_size);
    //     cube[3] = vec3( -cube_size,-cube_size, cube_size);
    //     cube[4] = vec3( -cube_size, cube_size,-cube_size);
    //     cube[5] = vec3(  cube_size, cube_size,-cube_size);
    //     cube[6] = vec3(  cube_size,-cube_size,-cube_size);
    //     cube[7] = vec3( -cube_size,-cube_size,-cube_size);

    //     for(int i = 0; i < 8; i++){
    //         sum += frustum_culling( modelMatrix * vec4(cube[i], 1.0));
    //     }

    //     if( sum >= 0.0){
    //         gl_Position = uProjView * modelMatrix * vec4( b, 1.0);
    //     }

    // }else{
    //     gl_Position = uProjView * modelMatrix * vec4( b, 1.0);
    // }
}