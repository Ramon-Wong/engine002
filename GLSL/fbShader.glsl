#version 400

in vec3             oArray2;            // texcoords
in vec2             oArray3;            // normals 
in float            _timer;

out vec4            fColor;             // Output fragment color

uniform sampler2D   tSampler; 

void main() {
    // Sample the texture
    vec4 texColor = texture(tSampler, oArray3);

    // Create a ripple distortion effect based on _timer
    float rippleX = sin(oArray2.y * 10.0 + _timer * 2.0); // Adjust frequency and animation speed
    float rippleY = cos(oArray2.x * 10.0 + _timer * 2.0); // Adjust frequency and animation speed
    vec2 distortedCoords = oArray3.xy + 0.02 * vec2(rippleX, rippleY); // Adjust distortion strength

    // Sample the texture using the distorted coordinates
    vec4 distortedColor = texture(tSampler, distortedCoords);

    // Blend the distorted color with the original color
    texColor = mix(texColor, distortedColor, 0.5); // Adjust blending strength

    fColor = texColor;
}
