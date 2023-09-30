#version 330 core

uniform mat4 u_modelMatrix; 
uniform mat4 u_viewMatrix;  
uniform mat4 u_projMatrix;

in vec3 inPosition;
in vec2 inTexCoord;

out vec2 TexCoord;


void main(){

    gl_Position = u_projMatrix * u_viewMatrix * u_modelMatrix * vec4(inPosition, 1.0);

    TexCoord = inTexCoord;

}
