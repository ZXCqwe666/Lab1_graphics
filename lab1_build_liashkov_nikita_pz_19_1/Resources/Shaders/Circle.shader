#shader vertex
#version 460 core

layout(location = 0) in vec4 position;

uniform mat4 u_MVP;

void main()
{
   gl_Position = u_MVP * position;
}

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

uniform vec2 u_origin;
uniform vec3 u_circleColor;
uniform float u_radius;
uniform float u_fade;

uniform vec2 u_resolution;

void main()
{
    vec2 uv = (gl_FragCoord.xy - u_origin) / u_resolution * 2.0 - 1.0;
    float aspect = u_resolution.x / u_resolution.y;
    uv.x *= aspect;
    
    float radius = u_radius / u_resolution.y;
    float distance = radius - length(uv);
    float alpha = smoothstep(0.0, u_fade, distance);
    
    color = vec4(u_circleColor, alpha);
}
