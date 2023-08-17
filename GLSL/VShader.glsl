#version 400

uniform mat4 uProjView;
uniform float PI;
uniform float rotate_z;

in vec3 inPosition;  // Input vertex position
in vec2 inTexCoord;

out vec2 texCoord;

void main() {
    vec3 a = inPosition;
    vec3 b = a;

    float rad_angle = rotate_z * PI / 180.0;

    b.x = a.x * cos(rad_angle) + a.y * sin(rad_angle);
    b.y = a.y * cos(rad_angle) - a.x * sin(rad_angle);

    gl_Position = uProjView * vec4(b, 1.0);
    texCoord = inTexcoord;
}