#version 330 core
out vec4 FragColor;
in vec3 TexCoord;
uniform samplerCube u_texture;

void main(){
    vec3 direction = normalize(TexCoord-0.5);
    FragColor=texture(u_texture, direction);
}

