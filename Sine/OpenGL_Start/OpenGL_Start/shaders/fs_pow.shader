#version 330 core
out vec4 FragColor;

void main() {
    // Define the range of x values
    float xMin = -10.0;
    float xMax = 10.0;
    
    // Define the exponent (you can change this value)
    float n = 2.0;
    
    // Calculate y for the given x
    float x = (gl_FragCoord.x / 1112.0) * (xMax - xMin) + xMin;
    float y = pow(x, n);
    
    // Map y to the range [0, 1] for coloring
    float yNormalized = (y - 0.0) / (1.0 - 0.0);
    
    // Assign a color based on y
    vec3 color = vec3(yNormalized, 0.0, 0.0);
    
    FragColor = vec4(color, 1.0);
}
