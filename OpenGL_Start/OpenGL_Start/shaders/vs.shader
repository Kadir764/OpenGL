#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projMatrix;

void main()
{
    TexCoord = aTexCoord;
    gl_Position = u_projMatrix * u_viewMatrix * u_modelMatrix * vec4(aPos, 1.0);
}
