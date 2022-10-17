#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;

out vec3 v_color;

uniform mat4 u_MVP;

void main()
{
   gl_Position = u_MVP * position;
   v_color = color;
}

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

in vec3 v_color;

void main()
{
   color = vec4(v_color, 1.0f);
}
