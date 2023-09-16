#version 400

uniform mat4 uProjView;
uniform float rotate_z;

in vec3     inPosition;             // Input vertex position
in vec3     iArray2;                // Input Colors
in vec3     iArray3;                // Input normals

out vec3    oArray2;                // Color out



void main() {
    vec3 a      = inPosition; 
    vec3 b      = a;

    oArray2     = iArray2;

    float rad_angle = rotate_z * 3.141592 / 180.0;
    b.x = a.x * cos(rad_angle) + a.y * sin(rad_angle);
    b.y = a.y * cos(rad_angle) - a.x * sin(rad_angle);

    gl_Position = uProjView * vec4( b, 1.0);
}