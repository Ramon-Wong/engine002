#version 400

uniform mat4    uProjView;
uniform float   timer;

uniform mat4    modelMatrix;


in vec3         inPosition;             // Input vertex position
in vec3         iArray2;                // Input tex_coords
in vec2         iArray3;                // Input normals

out vec3        oArray2;                // texcoords out
out vec2        oArray3;                // normal out
out float       _timer;


float frustum_culling(vec3 point){
    float       dotSum = 0.0f;
    vec4        plane[6];                       // planes, left, right, bottom, top, near and far

    plane[0] = uProjView[3] + uProjView[0];     // Left Plane
    plane[1] = uProjView[3] - uProjView[0];     // Right Plane
    plane[2] = uProjView[3] + uProjView[1];     // Bottom Plane
    plane[3] = uProjView[3] - uProjView[1];     // Top Plane
    plane[4] = uProjView[3] + uProjView[2];     // Near Plane
    plane[5] = uProjView[3] - uProjView[2];     // Far Plane
    
    for(int i = 0; i < 6; i++){
        dotSum += dot(plane[i], vec4( point, 1.0f));
    }

    return dotSum;
}



void main() {
    vec3 a      = inPosition; 
    vec3 b      = a;

    oArray2     = iArray2;
    oArray3     = iArray3;
    _timer      = timer;

    gl_Position = uProjView * modelMatrix * vec4( b, 1.0);
}