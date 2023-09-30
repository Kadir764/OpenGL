#version 330 core

out vec4 FragColor; // Output color to framebuffer

uniform vec2 u_resolution;
uniform float u_time;

vec3 hsb2rgb(in vec3 c){
    vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0,4.0,2.0), 6.0)-3.0)-1.0, 0.0, 1.0);
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return c.z * mix(vec3(1.0), rgb, c.y);
}

void main(){
    vec2 st = gl_FragCoord.xy / u_resolution;
    
    // Apply a sine wave effect to the y-coordinate
    float waveFactor = sin(st.x * 10.0 + u_time) * 0.1;
    st.y += waveFactor;
    
    // Calculate hue value based on time (u_time) and x-coordinate (st.x)
    float hue = mod(u_time * 0.2 + st.x, 1.0);
    
    // Set saturation and brightness to constant values
    float saturation = 1.0;
    float brightness = 1.0;
    
    vec3 color = hsb2rgb(vec3(hue, saturation, brightness));
    
    FragColor = vec4(color, 1.0);
}
