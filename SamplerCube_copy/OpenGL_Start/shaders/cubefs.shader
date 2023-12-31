#version 330 core
out vec4 FragColor;

in vec3 TexCoords;
uniform samplerCube u_texture;

void main()
{
    vec3 direction = normalize(TexCoords);
    FragColor = texture(u_texture, direction);
}
