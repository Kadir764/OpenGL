#version 330 core
precision mediump float;
uniform vec3 triangle1Position;
uniform vec3 triangle2Position;
in vec3 fragColor; // Change this to an input varying variable
out vec4 FragColor;
in vec2 TexCoord; // Assuming you have texture coordinates for your fragment
uniform sampler2D text; // The text texture
in float dist;

void main() {
    // Calculate the vector between the centers of the triangles
    //vec3 center1 = triangle1Position;
    //vec3 center2 = triangle2Position;
    //vec3 centerVector = center2 - center1;

    // Calculate the 3D distance
    float dist = distance(triangle1Position, triangle2Position);
    
     // Pass the distance as a varying variable
    
    FragColor = vec4(1.0 - dist/2.0, dist/2.0, 0.5, 1.0);
    
}
