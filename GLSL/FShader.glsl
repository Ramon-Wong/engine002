#version 330

in vec2                 texCoord;
uniform sampler2D       u_texture;
out vec4                fragment;


void main() {
  fragment = vec4(1.0, 1.0, 1.0, 1.0);
}

