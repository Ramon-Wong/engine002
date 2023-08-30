#version 400

uniform mat4 uProjView;

in vec3 inPosition;  // Input vertex position
out vec4 fragColor;  // Output fragment color (you can modify this based on your needs)

void main() {
    vec3 a = inPosition;

    gl_Position = uProjView * vec4(a, 1.0);
    fragColor = vec4(1.0, 1.0, 1.0, 1.0);  // Example: setting the fragment color to white
}