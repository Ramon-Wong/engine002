#version 400

in vec3             oArray2;            // colors in
out vec4            fColor;             // Output fragment color

void main() {
    fColor = vec4( oArray2, 1.0);
}