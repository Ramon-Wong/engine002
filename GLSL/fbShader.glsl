#version 400

in vec3 oArray2;            // Normals
in vec2 oArray3;            // Texcoords 

out vec4 fColor;            // Output fragment color

uniform sampler2D tSampler;

void main() {
    // Sample the texture
    vec4 texColor = texture(tSampler, oArray3);

    // Define the light direction (for example, a directional light)
    vec3 lightDirection = normalize(vec3( 1.0, 2.0, -4.0)); // Adjust the light direction

    // Normalize the normal vector to ensure it has a length of 1
    vec3 normal = oArray2;

    // Calculate the dot product between the normal and light direction
    float diffuse = max(dot(normal, lightDirection), 0.40);

    // Define the base color of the surface
    vec3 baseColor = vec3(1.0, 1.0, 1.0); // Adjust the base color

    // Calculate the final color by applying diffuse lighting
    vec3 finalColor = baseColor * diffuse;

    // Set the output color
    fColor = vec4(finalColor * texColor.rgb, texColor.a);
}
