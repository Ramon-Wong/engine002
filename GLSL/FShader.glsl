#version 400

in vec2 texCoord;  // Input texture coordinates from the vertex shader

uniform sampler2D u_texture;  // Texture sampler uniform

out vec4 finalColor;  // Output fragment color

void main() {
    vec4 textureColor = texture(u_texture, texCoord);  // Sample the texture using the interpolated texture coordinates
    finalColor = textureColor;
}