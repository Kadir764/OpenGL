#version 330 core
layout (location = 0) in vec3 aPos;
out vec3 TexCoords;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projMatrix;

void main()
{
    TexCoords = aPos;  // Use the vertex position as texture coordinates
    gl_Position = u_projMatrix * u_viewMatrix * u_modelMatrix * vec4(aPos, 1.0);
}
