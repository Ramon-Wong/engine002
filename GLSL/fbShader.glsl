#version 400

in vec3             oArray2;            // texcoords
in vec2             oArray3;            // normals 
in float            _timer;

out vec4            fColor;             // Output fragment color

uniform sampler2D   tSampler; 

void main() {
    // Sample the texture
    vec4 texColor = texture(tSampler, oArray3);

    // Create a colorful vortex effect based on _timer
    float angle = _timer * 6.0; // Adjust animation speed
    float radius = length(oArray2); // Calculate distance from center
    vec2 distortedCoords = oArray3.xy + 0.02 * radius * vec2(cos(angle), sin(angle)); // Adjust distortion strength

    // Sample the texture using the distorted coordinates
    vec4 distortedColor = texture(tSampler, distortedCoords);

    // Blend the distorted color with the original color
    texColor = mix(texColor, distortedColor, 0.7); // Adjust blending strength

    // Apply bloom to bright areas of the image
    if (texColor.r > 0.7) {
        texColor.rgb += 0.5 * (texColor.rgb - 0.7); // Add a portion of the overbright color
    }

    fColor = texColor;
}
