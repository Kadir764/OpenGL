#version 330 core

in vec2 TexCoord;
in vec2 FragTexCoord;

uniform sampler2D u_texture; 
uniform vec2 u_resolution;
uniform float u_time;



out vec4 FragColor; 



lowp vec3 hsb2rgb(in lowp vec3 c){
    vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0,4.0,2.0), 6.0)-3.0)-1.0, 0.0, 1.0);
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return c.z * mix(vec3(1.0), rgb, c.y);
}

void main(){
    lowp vec2 st = TexCoord;
    
    
    float waveFactor = sin(st.x * 10.0 + u_time) * 0.1;
    st.y += waveFactor;
    
    float hue = mod(u_time * 0.2 + st.x, 1.0);
    float saturation = 1.0;
    float brightness = 1.5;


    vec3 hsbColor = vec3(hue, saturation, brightness);
    vec3 rgbColor = hsb2rgb(hsbColor);

    vec2 finalTexCoord = mix(TexCoord, FragTexCoord, 0.5);

    vec4 textureColor = texture(u_texture, finalTexCoord);

    vec3 finalColor = textureColor.rgb * rgbColor;

    FragColor = vec4(finalColor, 1.0);
    //vec4 textureColor = texture(u_texture, finalTexCoord);

    //vec4 finalColor = textureColor;


    //FragColor = vec4(finalColor);
}
