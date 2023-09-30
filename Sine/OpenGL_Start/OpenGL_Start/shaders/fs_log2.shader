#version 330 core
out vec4 FragColor;

void main() {
    // Define the range of x values
    float xMin = -10.0;
    float xMax = 10.0;
    float amplitude = 0.5f;
    float frequency = 1.0f;
    float phaseShift = 0.0f;
    
    // Calculate y for the given x
    float x = (gl_FragCoord.x / 1112.0) * (xMax - xMin) + xMin;
    float y = amplitude * log2(x);
    
    // Map y to the range [0, 1] for coloring
    float yNormalized = (y - 0.0) / (1.0 - 0.0);
    
    // Assign a color based on y
    vec3 color = vec3(yNormalized, 0.0, 0.0);
    
    FragColor = vec4(color, 1.0);
}
