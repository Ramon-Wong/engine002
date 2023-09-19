#version 400

in vec3             oArray2;            // texcoords
in vec2             oArray3;            // normals 
in float            _timer;

out vec4            fColor;             // Output fragment color

uniform sampler2D   tSampler; 

void main() {
    // Sample the texture
    vec4 texColor = texture(tSampler, oArray3);

    // Create a pulsating color effect based on _timer
    float pulseIntensity = abs(sin(_timer)); // Use sine wave for pulsation

    // Apply the pulsating effect to the color
    texColor.rgb *= pulseIntensity; // Multiply color by pulsation intensity

    fColor = texColor;
}
