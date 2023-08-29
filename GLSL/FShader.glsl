#version 330

in vec2             vTextureCoordinates;
uniform sampler2D   uTexture; 

out vec4            fragmentColor;

void main() {
    fragmentColor = texture(uTexture, vTextureCoordinates);
}